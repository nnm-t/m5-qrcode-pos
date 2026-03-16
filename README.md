# M5Stack 使用 同人誌即売会用レジ端末 (QR Code POS Terminal for M5Stack)

## 概要

コミックマーケット等、同人誌即売会での会計処理を念頭に置いて開発したレジ端末のファームウェア。
ハードウェアは M5Stack Core2 を使用し、はんだ付けを伴う組み立てを必要としない。

M5Stack Faces を使用する拙作 [m5stack-sokubai-pos](https://github.com/nnm-t/m5stack-sokubai-pos) は2019年開発で設計が古くなっており、パーツの入手も難しくなってきたので、2代目として新規に設計した。

### 機能

- M5Stack のディスプレイに搭載されたタッチパネルですべての操作が可能
  - HMI Module のエンコーダとスイッチでの操作も可能
- 登録済み商品のカウント・売上記録
  - 商品データは JSON 形式で読み込む
  - サムネイル画像の表示が可能
- バーコード/QRコードを読み取り、登録済み商品をカウント
- 未登録商品の金額入力
- 登録済み商品・金額入力それぞれの売上一覧の表示
  - 売上データは JSON 形式で保存
  - 売上データに時刻を付加して CSV 形式での書き出しにも対応
- 時刻表示・設定、バッテリ残量表示

## 商品データ

使用にあたり、定められた仕様で記述した `goods.json` と `sales.json` の2つの JSON ファイルを MicroSD カードのルートディレクトリにコピーし、カードを M5Stack のカードスロットに装着する必要がある。

### `goods.json` ([サンプル](https://github.com/nnm-t/m5-qrcode-pos/blob/master/json/goods.json))

```json
{
    "goods": [
        {
            "name": "商品0",
            "image_path": "/image_0.bmp",
            "price": 500,
            "code": "9999999999999"
        },
        {
            "name": "商品1",
            "image_path": "/image_1.bmp",
            "price": 1000,
            "code": "9999999999999"
        }
    ]
}
```

- `goods`: 商品 (配列形式)
  - `name`: 商品名
  - `image_path`: サムネイル画像 (120 x 120 Windows Bitmap) のパス
  - `price`: 価格 (円)
  - `code`: QRコードリーダで読み取った時の値 (使用しなければ適当な文字列で埋める)

### `sales.json` ([サンプル](https://github.com/nnm-t/m5-qrcode-pos/blob/master/json/sales.json))

```json
{
    "goods": [
        0,
        0
    ],
    "amounts": {}
}
```

- `goods`: 商品の売上 (配列形式)
  - 値の要素数は `goods.json` での商品データの要素数と同一にする
- `amounts`: 金額入力の売上
  - 中括弧の中は空で構わない

## 対応機種

日本国内では[スイッチサイエンス](https://www.switch-science.com/)等で正規ルート品を入手可能。

- [M5Stack Core2](https://docs.m5stack.com/ja/core/core2)
  - 基本構成が同一の [Core2 v1.1](https://docs.m5stack.com/ja/core/Core2%20v1.1)/[Core2 For AWS](https://docs.m5stack.com/ja/core/core2_for_aws) 等にも対応
  - [CoreS3](https://docs.m5stack.com/ja/core/CoreS3)/[CoreS3 SE](https://docs.m5stack.com/ja/core/M5CoreS3%20SE)/[CoreS3 Lite](https://docs.m5stack.com/ja/core/CoreS3-Lite) 等での動作も考慮 (未確認)
- [Module HMI](https://docs.m5stack.com/ja/module/HMI%20Module) (オプション)
- [Moodule13.2 QRCode](https://docs.m5stack.com/ja/module/Module13.2_QRCode) (オプション)
- [Base AAA](https://docs.m5stack.com/ja/base/base_aaa) (オプション)
  - Base をこれに交換すると単4電池4本で長時間駆動が可能
  - CoreS3 シリーズでは満充電でも起動しないので、起動時のみ USB から給電する

## 開発環境

大人の事情で PlatformIO の ESP32 対応がストップしているため pioarduino を使用。
Visual Studio Code では [pioarduino IDE](https://marketplace.visualstudio.com/items?itemName=pioarduino.pioarduino-ide) をインストールして環境構築できる。

- pioarduino: [platform-espressif32](https://github.com/pioarduino/platform-espressif32)
  - Arduino Platform
  - v0.1 時点で Arduino 3.3.7 + ESP-IDF 5.5.2 でビルド

### `lv_conf.h` の設定

本リポジトリに含まれない `.pio/libdeps/m5stack-core2/lvgl/lv_conf.h` はユーザ自身で編集する。
なお `m5stack-core2` の部分は使用するマイコンボードによって変わる。

まずは `.pio/libdeps/m5stack-core2/lvgl/lv_conf_template.h` を同一ディレクトリ上に複製し `lv_conf.h` にリネームする。

LVGL 9.4 では 15行目にある `#if` ディレクティブの値を `0` から `1` に変更する。

```c
#if 1
```

LVGL 9.4 では 935, 941, 945 行目にある、画像デコーダに関する `#define` を `0` から `1` に変更して有効化する。

```c
#define LV_USE_LODEPNG 1

#define LV_USE_BMP 1

#define LV_USE_TJPGD 1
```

キャッシュ機能を持たせたファイルシステムを独自に実装しているので `LV_USE_FS_ARDUINO_SD` (LVGL 9.4 では 917 行目) 等を変更する必要はない。

## ライセンス

- [M5Unified](https://github.com/m5stack/M5Unified): [MIT](https://github.com/m5stack/M5Unified/blob/master/LICENSE)
- [M5GFX](https://github.com/m5stack/M5GFX): [MIT](https://github.com/m5stack/M5GFX/blob/master/LICENSE)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson): [MIT](https://github.com/bblanchon/ArduinoJson/blob/7.x/LICENSE.txt)
- [LVGL](https://github.com/lvgl/lvgl): [MIT](https://github.com/lvgl/lvgl/blob/master/LICENCE.txt)
- [M5Module-HMI](https://github.com/m5stack/M5Module-HMI): [MIT](https://github.com/m5stack/M5Module-HMI/blob/main/LICENSE)
- [M5Module-QRCode](https://github.com/m5stack/M5Module-QRCode): [MIT](https://github.com/m5stack/M5Module-QRCode/blob/main/LICENSE)
- [Noto Sans Japanese](https://fonts.google.com/noto/specimen/Noto+Sans+JP): [OFL-1.1](https://fonts.google.com/noto/specimen/Noto+Sans+JP/license)
- [DSEG](https://github.com/keshikan/DSEG): [OFL-1.1](https://github.com/keshikan/DSEG/blob/master/DSEG-LICENSE.txt)
