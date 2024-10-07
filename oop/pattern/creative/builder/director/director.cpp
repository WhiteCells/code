#include "director.h"

void Director::setBuilder(Builder *builder) {
    builder_ = builder;
}

Product Director::constructProduct() {
    builder_->buildAttributeA();
    builder_->buildAttributeB();
    builder_->buildAttributeC();
    return builder_->getProduct();
}