#include "lv_fs_sd_memfs.h"

#if LV_USE_FS_ARDUINO_SD == 0

static void* fs_open(lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close(lv_fs_drv_t* drv, void* file_p);
static lv_fs_res_t fs_read(lv_fs_drv_t* drv, void* file_p, void* buf, uint32_t btr, uint32_t* br);
static lv_fs_res_t fs_seek(lv_fs_drv_t* drv, void* file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t fs_tell(lv_fs_drv_t* drv, void* file_p, uint32_t* pos_p);

typedef struct {
    size_t id;
    size_t size;
    char* buffer;
    uint32_t position;
} fs_cache_t;

static fs_cache_t fs_cache = {};

extern "C" void lv_fs_clear_cache()
{
    fs_cache.id = 0;
    fs_cache.size = 0;
    fs_cache.position = 0;
    
    if (fs_cache.buffer) {
        free(fs_cache.buffer);
        fs_cache.buffer = 0;
    }
}

extern "C" void lv_fs_arduino_sd_init()
{
    static lv_fs_drv_t fs_drv;
    lv_fs_drv_init(&fs_drv);

    fs_drv.letter = USER_FS_ARDUINO_SD_LETTER;
    fs_drv.open_cb = fs_open;
    fs_drv.close_cb = fs_close;
    fs_drv.read_cb = fs_read;
    fs_drv.write_cb = nullptr;
    fs_drv.seek_cb = fs_seek;
    fs_drv.tell_cb = fs_tell;

    fs_drv.dir_close_cb = nullptr;
    fs_drv.dir_open_cb = nullptr;
    fs_drv.dir_read_cb = nullptr;

    lv_fs_drv_register(&fs_drv);
}

static void* fs_open(lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode)
{
    LV_UNUSED(drv);
    LV_UNUSED(mode);

    std::hash<std::string> makeHash;
    size_t id = makeHash(path);

    if (id != fs_cache.id)
    {
        lv_fs_clear_cache();
        fs_cache.id = id;

        File file = SD.open(path, FILE_READ);
        size_t size = file.size();
        fs_cache.buffer = (char*)malloc(size);
        assert(fs_cache.buffer);

        fs_cache.size = file.read((uint8_t*)fs_cache.buffer, size);
        assert(fs_cache.size == size);

        file.close();
    }

    fs_cache.position = 0;
    return (void*)drv;
}

static lv_fs_res_t fs_close(lv_fs_drv_t* drv, void* file_p)
{
    LV_UNUSED(drv);
    LV_UNUSED(file_p);

    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_read(lv_fs_drv_t* drv, void* file_p, void* buf, uint32_t btr, uint32_t* br)
{
    LV_UNUSED(drv);
    LV_UNUSED(file_p);

    if (fs_cache.position >= 0 && fs_cache.position <= fs_cache.size)
    {
        uint32_t remaining = fs_cache.size - fs_cache.position;
        if (btr > remaining)
        {
            btr = remaining;
        }

        memcpy(buf, fs_cache.buffer + fs_cache.position, btr);
        fs_cache.position += (*br = btr);

        return LV_FS_RES_OK;
    }

    assert(false);
    *br = 0;
    return LV_FS_RES_INV_PARAM;
}

static lv_fs_res_t fs_seek(lv_fs_drv_t* drv, void* file_p, uint32_t pos, lv_fs_whence_t whence)
{
    LV_UNUSED(drv);
    LV_UNUSED(file_p);

    switch (whence)
    {
        case LV_FS_SEEK_SET:
            fs_cache.position = pos;
            break;
        case LV_FS_SEEK_CUR:
            fs_cache.position += pos;
            break;
        case LV_FS_SEEK_END:
            fs_cache.position = (fs_cache.size - 1) - pos;
            break;
    }

    assert(fs_cache.position < fs_cache.size);
    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_tell(lv_fs_drv_t* drv, void* file_p, uint32_t* pos_p)
{
    LV_UNUSED(drv);
    LV_UNUSED(file_p);

    *pos_p = fs_cache.position;
    return LV_FS_RES_OK;
}

#endif