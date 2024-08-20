#ifndef _IO_THREAD_POOL_H_
#define _IO_THREAD_POOL_H_

#include <boost/asio.hpp>
#include <memory>
#include <vector>

namespace asio = boost::asio;

class IoThreadPool {
    using Work = asio::io_context::work;

public:
    ~IoThreadPool();
    static IoThreadPool &getInstance();
    asio::io_context &getIoContext();

private:
    IoThreadPool(std::size_t thread_num = std::thread::hardware_concurrency());
    IoThreadPool(const IoThreadPool &) = delete;
    IoThreadPool &operator=(const IoThreadPool &) = delete;

    asio::io_context ioc_;
    std::unique_ptr<Work> work_;
    // multiple threads io_context run handle events
    std::vector<std::thread> run_threads_;
};

#endif // _IO_THREAD_POOL_H_