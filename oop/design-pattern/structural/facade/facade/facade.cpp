#include "facade.h"

Facade::Facade() {
    system_a_ = new SystemA();
    system_b_ = new SystemB();
    system_c_ = new SystemC();
}

Facade::~Facade() {
    if (system_a_) {
        delete system_a_;
        system_a_ = nullptr;
    }
    if (system_b_) {
        delete system_b_;
        system_b_ = nullptr;
    }
    if (system_c_) {
        delete system_c_;
        system_c_ = nullptr;
    }
}

void Facade::wrapSystemOperate() {
    system_a_->operateA();
    system_b_->operateB();
    system_c_->operateC();
}