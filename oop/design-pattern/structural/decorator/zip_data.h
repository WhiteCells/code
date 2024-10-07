#ifndef _ZIP_DATA_H_
#define _ZIP_DATA_H_

#include "decorate_data.h"

class ZipData : public DecorateData {
public:
    using DecorateData::DecorateData;
    virtual void output(std::string data) override {
        data_->output("zip " + data);
    }
};

#endif // _ZIP_DATA_H_