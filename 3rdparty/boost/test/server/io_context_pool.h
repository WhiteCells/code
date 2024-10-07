#ifndef _IO_CONTEXT_POOL_H_
#define _IO_CONTEXT_POOL_H_

#include "singleton.hpp"
#include <boost/asio.hpp>
#include <vector>
#include <thread>

class IOContextPool :
    public Singleton<IOContextPool> {
    
    friend class Singleton<IOContextPool>;
    using IOContext = boost::asio::io_context;
    using Work = boost::asio::io_context::work;
    using WorkUPtr = std::unique_ptr<Work>;

public:
    ~IOContextPool();
    IOContext &getIoContext();
    void stopAllContext();

private:
    IOContextPool(std::size_t pool_size = 2);

    std::vector<IOContext> io_contexts_;
    std::vector<WorkUPtr> works_;
    std::vector<std::thread> threads_;
    std::size_t next_io_context_;
};

#endif // _IO_CONTEXT_POOL_H_