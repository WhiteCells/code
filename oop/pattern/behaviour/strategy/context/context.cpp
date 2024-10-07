#include "context.h"

Context::Context(Strategy *strategy)
    : strategy_(strategy) {

}

Context::~Context() {
    if (strategy_) {
        delete strategy_;
        strategy_ = nullptr;
    }
}

void Context::setStrategy(Strategy *strategy) {
    if (strategy_) {
        delete strategy_;
        strategy_ = nullptr;
    }
    strategy_ = strategy;
}

void Context::process() {
    strategy_->execute();
}