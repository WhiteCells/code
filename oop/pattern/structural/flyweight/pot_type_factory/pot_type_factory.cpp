#include "pot_type_factory.h"

PotTypeFactory *PotTypeFactory::instance_ = nullptr;

std::mutex PotTypeFactory::mutex_;

PotTypeFactory *PotTypeFactory::getInstance() {
    static CleanUp clean_up;
    if (!instance_) {
        mutex_.lock();
        if (!instance_) {
            instance_ = new PotTypeFactory();
        }
        mutex_.unlock();
    }
    return instance_;
}

PotType *PotTypeFactory::getPot(std::string id, std::string color, double size) {
    std::string key = id + color + std::to_string(size);
    PotType *val = nullptr;
    if (pot_types_.count(key)) {
        val = pot_types_[key];
    } else {
        val = new PotType(id, color, size);
        pot_types_[key] = val;
    }
    return val;
}

PotTypeFactory::PotTypeFactory() {

}

PotTypeFactory::~PotTypeFactory() {
    for (auto &iter : pot_types_) {
        if (iter.second) {
            delete iter.second;
            iter.second = nullptr;
        }
    }
    pot_types_.clear();
}

PotTypeFactory::CleanUp::~CleanUp() {
    if (PotTypeFactory::instance_) {
        delete PotTypeFactory::instance_;
        PotTypeFactory::instance_ = nullptr;
    }
}