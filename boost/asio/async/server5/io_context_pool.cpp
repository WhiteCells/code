#include "io_context_pool.h"
#include <iostream>

IoContextPool::~IoContextPool() {
    std::cout << "~IoContextPool()" << std::endl;

    // all asio::io_context::work supervised asio::io_context stop
    for (auto &work : works_) {
        work->get_io_context().stop();
        work.reset();
    }

    for (auto &run_thread : run_threads_) {
        run_thread.join();
    }
}

IoContextPool &IoContextPool::getInstance() {
    static IoContextPool io_context_pool;
    return io_context_pool;
}

asio::io_context &IoContextPool::getIoContext() {
    // an asio::io_context can listen to events from multiple sockets
    asio::io_context &ioc = io_contexts_[io_contexts_idx_++];
    if (io_contexts_idx_ >= io_contexts_.size()) {
        io_contexts_idx_ = 0;
    }
    return ioc;
}

IoContextPool::IoContextPool(std::size_t pool_size) :
    io_contexts_idx_(0),
    works_(pool_size),
    io_contexts_(pool_size) {

    // work oversee asio::io_context
    for (std::size_t i = 0; i < pool_size; ++i) {
        works_[i] = std::make_unique<Work>(io_contexts_[i]);
    }

    // asio::io_context run() in separate thread
    for (std::size_t i = 0; i < pool_size; ++i) {
        run_threads_.emplace_back([i, this]() {
            io_contexts_[i].run();
        });
    }
}