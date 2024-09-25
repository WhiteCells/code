#ifndef _GRPC_CONNECTION_POO_H_
#define _GRPC_CONNECTION_POO_H_

#include <grpcpp/grpcpp.h>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <queue>
#include <memory>
#include <string>

template <typename T>
class GrpcConnectionPool
{
public:
    GrpcConnectionPool(
        std::size_t pool_size,
        const std::string &host,
        const std::string &port);
    GrpcConnectionPool(const GrpcConnectionPool &) = delete;
    GrpcConnectionPool(GrpcConnectionPool &&) = delete;
    GrpcConnectionPool &operator=(const GrpcConnectionPool &) = delete;
    GrpcConnectionPool &operator=(GrpcConnectionPool &&) = delete;
    ~GrpcConnectionPool();

    std::unique_ptr<T> getConnection();
    void recycleConnection(std::unique_ptr<T> connection);
    void stopAllConnection();

private:
    std::size_t pool_size_;
    std::string host_;
    std::string port_;
    std::atomic_bool has_stop_;
    std::mutex que_mtx_;
    std::condition_variable que_cv_;
    std::queue<std::unique_ptr<T>> connection_que_;
};

// T std::Stub
template <typename T>
GrpcConnectionPool<T>::GrpcConnectionPool(
    std::size_t pool_size,
    const std::string &host,
    const std::string &port) :
    pool_size_(pool_size),
    host_(host),
    port_(port),
    has_stop_(false)
{
    for (std::size_t i = 0; i < pool_size_; ++i) {
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(
            host_ + ":" + port_,
            grpc::InsecureChannelCredentials());
        connection_que_.push(std::make_unique<T>(channel));
    }
}

template <typename T>
GrpcConnectionPool<T>::~GrpcConnectionPool()
{
    std::unique_lock<std::mutex> ulock(que_mtx_);
    while (!connection_que_.empty()) {
        connection_que_.pop();
    }
}

template <typename T>
std::unique_ptr<T> GrpcConnectionPool<T>::getConnection()
{
    std::unique_ptr<T> connection;
    {
        std::unique_lock<std::mutex> ulock(que_mtx_);
        que_cv_.wait(ulock, [this]() {
            return !connection_que_.empty() || has_stop_;
        });
        if (has_stop_) {
            return nullptr;
        }
        connection = std::move(connection_que_.front());
        connection_que_.pop();
    }
    return connection;
}

template <typename T>
void GrpcConnectionPool<T>::recycleConnection(std::unique_ptr<T> connection)
{
    if (has_stop_) {
        return;
    }
    {
        std::lock_guard<std::mutex> lock(que_mtx_);
        connection_que_.push(std::move(connection));
    }
    que_cv_.notify_one();
}

template <typename T>
void GrpcConnectionPool<T>::stopAllConnection()
{
    has_stop_ = true;
    que_cv_.notify_all();
}

#endif // _GRPC_CONNECTION_POO_H_