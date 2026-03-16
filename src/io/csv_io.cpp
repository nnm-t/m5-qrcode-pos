#include "io/csv_io.h"

void CsvIO::Write(std::string& csv_line)
{
    File file = SD.open(file_name, FILE_APPEND);
    
    if (file.size() == 0)
    {
        file.println(_goods.GetCommaSeparatedAllNames().c_str());
    }

    file.println(csv_line.c_str());

    file.close();
}