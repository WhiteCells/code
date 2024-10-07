#include "io_thread_pool.h"
#include <iostream>

IoThreadPool::~IoThreadPool() {
    std::cout << "~IoThreadPool()" << std::endl;
    work_->get_io_context().stop();
    work_.reset();
    for (auto &run_thread : run_threads_) {
        run_thread.join();
    }
}

IoThreadPool &IoThreadPool::getInstance() {
    static IoThreadPool io_thread_pool;
    return io_thread_pool;
}

asio::io_context &IoThreadPool::getIoContext() {
    return ioc_;
}

IoThreadPool::IoThreadPool(std::size_t thread_num) :
    work_(std::make_unique<Work>(ioc_)){

    for (std::size_t i = 0; i < thread_num; ++i) {
        run_threads_.emplace_back([this]() {
            ioc_.run();
        });
    }
}
