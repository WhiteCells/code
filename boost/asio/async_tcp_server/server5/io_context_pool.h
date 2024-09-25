#ifndef _IO_CONTEXT_POOL_H_
#define _IO_CONTEXT_POOL_H_

#include <boost/asio.hpp>
#include <thread>
#include <memory>
#include <vector>

namespace asio = boost::asio;

class IoContextPool
{
    using IoContext = asio::io_context;
    // when io_context has no bound events, io_context will end
    // work to tie asio::io_context, prevent asio::io_context run() return
    using Work = asio::io_context::work;
    using WorkUPtr = std::unique_ptr<Work>;

public:
    static IoContextPool &getInstance();
    asio::io_context &getIoContext();

private:
    IoContextPool(std::size_t pool_size = std::thread::hardware_concurrency());
    IoContextPool(const IoContextPool &) = delete;
    IoContextPool &operator=(const IoContextPool &) = delete;
    ~IoContextPool();

    int io_contexts_idx_;                  // next io_context index
    std::vector<WorkUPtr> works_;          // oversee asio::io_context
    std::vector<IoContext> io_contexts_;   // io_context pool
    std::vector<std::thread> run_threads_; // asio::io_context runs on a separate thread
};

#endif // _IO_CONTEXT_POOL_H_