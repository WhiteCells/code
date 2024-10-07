#ifndef _UNZIP_DATA_H_
#define _UNZIP_DATA_H_

#include "decorate_data.h"

class UnzipData : public DecorateData {
public:
    using DecorateData::DecorateData;
    virtual void output(std::string data) override {
        data_->output("unzip " + data);
    }
};

#endif // _UNZIP_DATA_H_