#ifndef _FILE_DATA_H_
#define _FILE_DATA_H_

#include "data.h"
#include <iostream>

class FileData : public Data {
public:
    explicit FileData(std::string file_name) : file_name_(file_name) {}
    virtual void output(std::string data) override {
        printf("file: (%s), output: (%s)\n", file_name_.c_str(), data.c_str());
    }

private:
    std::string file_name_;
};

#endif // _FILE_DATA_H_