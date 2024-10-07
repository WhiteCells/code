#ifndef _DATA_DECORATOR_H_
#define _DATA_DECORATOR_H_

#include "data.h"

class DecorateData : public Data {
public:
    explicit DecorateData(Data *data) : data_(data) {}
    virtual void output(std::string data) override {
        data_->output("decorate " + data);
    }

protected:
    Data *data_;
};

#endif // _DATA_DECORATOR_H_