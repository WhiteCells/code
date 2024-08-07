#include "redis_connection_pool.h"
#include "global.h"
#include <iostream>

RedisConnectionPool::RedisConnectionPool(const std::size_t pool_size,
                                         const std::string &host,
                                         const int port,
                                         const std::string &user,
                                         const std::string &pass) :
    pool_size_(pool_size),
    host_(host),
    port_(port),
    user_(user),
    pass_(pass),
    has_stop_(false) {

    for (std::size_t i = 0; i < pool_size_; ++i) {
        redisContext *connection = redisConnect(host_.c_str(), port);
        if (!connection || connection->err) {
            if (connection) {
                ERROR("connection error: %s", connection->errstr);
                redisFree(connection);
                --i;
                continue;
            }
            ERROR("connection is null");
            --i;
            continue;
        }
        INFO("connection successed");

        redisReply *reply = static_cast<redisReply *>(
            redisCommand(connection, "auth %s %s", user_.c_str(), pass.c_str()));
        // std::unique_ptr<redisReply> reply = std::make_unique<redisReply>(redisCommand(connection, "auth %s %s", user_.c_str(), pass.c_str()));
        // std::unique_ptr<redisReply> reply((redisReply *)redisCommand(connection, "auth %s %s", user_.c_str(), pass.c_str()));
        Defer defer([&reply]() {
            freeReplyObject(reply);
        });
        if (!reply || reply->type == REDIS_REPLY_ERROR) {
            if (reply) {
                ERROR("redisCommand failed");
                continue;
            }
            ERROR("reply is null");
            redisFree(connection);
        }
        INFO("auth success");

        connections_.push(connection);
        INFO("push connection to pool");
    }
}

redisContext *RedisConnectionPool::getConnection() {
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this]() {
        return has_stop_ || !connections_.empty();
    });
    if (has_stop_) {
        return nullptr;
    }
    auto connection = connections_.front();
    connections_.pop();
    return connection;
}

void RedisConnectionPool::recycleConnection(redisContext *connection) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (has_stop_) {
        return;
    }
    connections_.push(connection);
    condition_.notify_one();
    INFO("recycle connection successed");
}

void RedisConnectionPool::stopAllConnection() {
    std::lock_guard<std::mutex> lock(mutex_);
    has_stop_ = true;
    condition_.notify_all();
    INFO("stop all connection successed");
}