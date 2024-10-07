#include "file_data.h"
#include "decorate_data.h"
#include "zip_data.h"
#include "unzip_data.h"

int main(int argc, char *argv[]) {
    FileData *file = new FileData("file1");
    file->output("hello");

    DecorateData *decorate_data = new DecorateData(file);
    decorate_data->output("hello");

    ZipData *zip_data = new ZipData(file);
    zip_data->output("hello");

    UnzipData *unzip_data = new UnzipData(file);
    unzip_data->output("hello");

    delete zip_data;
    delete decorate_data;
    delete file;
    return 0;
}