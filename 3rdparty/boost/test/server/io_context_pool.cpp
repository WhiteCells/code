#include "io_context_pool.h"

IOContextPool::~IOContextPool() {
    stopAllContext();
}

IOContextPool::IOContext &IOContextPool::getIoContext() {
    IOContext &context = io_contexts_[next_io_context_];
    if (next_io_context_ == io_contexts_.size()) {
        next_io_context_ = 0;
    }
    return context;
}

void IOContextPool::stopAllContext() {
    for (auto &work : works_) {
        work->get_io_context().stop();
        work.reset();
    }

    for (auto &thread : threads_) {
        thread.join();
    }
}

IOContextPool::IOContextPool(std::size_t pool_size) :
    io_contexts_(pool_size),
    works_(pool_size),
    next_io_context_(0) {

    for (std::size_t i = 0; i < pool_size; ++i) {
        works_[i] = std::make_unique<Work>(io_contexts_[i]);
    }

    for (std::size_t i = 0; i < io_contexts_.size(); ++i) {
        threads_.emplace_back([this, i]() {
            io_contexts_[i].run();
        });
    }
}