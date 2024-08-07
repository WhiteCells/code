#ifndef _REDIS_CONNECTION_POOL_H_
#define _REDIS_CONNECTION_POOL_H_

#include <hiredis/hiredis.h>
#include <memory>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>

class RedisConnectionPool {
public:
    RedisConnectionPool(const std::size_t pool_size,
                        const std::string &host,
                        const int port,
                        const std::string &user,
                        const std::string &pass);
    redisContext *getConnection();
    void recycleConnection(redisContext * connection);
    void stopAllConnection();

private:
    std::size_t pool_size_;
    std::string host_;
    int port_;
    std::string user_;
    std::string pass_;
    std::mutex mutex_;
    std::atomic_bool has_stop_;
    std::condition_variable condition_;
    std::queue<redisContext *> connections_;
};

#endif // _REDIS_CONNECTION_POOL_H_