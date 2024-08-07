#include "redis_manager.h"
#include "global.h"

#define REDIS_COMMAND(connection, format, ...) \
    static_cast<redisCommand *>(redisCommand(connection, format, ##__VA_ARGS__))

RedisManager::~RedisManager() {
    redis_connections_pool_->stopAllConnection();
}

bool RedisManager::get(const std::string &key, std::string &val) {
    auto connection = redis_connections_pool_->getConnection();
    if (!connection) {
        ERROR("connection pool failed to obtain connection");
        return false;
    }
    redisReply *reply = static_cast<redisReply *>(redisCommand(connection, "get %s", key.c_str()));
    // redisReply *reply = REDIS_COMMAND(connection, "get %s", key.c_str());
    // Defer defer([this, &connection, &reply]() {
    //     freeReplyObject(reply);
    //     redisFree(connection);
    // });
    if (!reply) {
        
    }

}

bool RedisManager::set(const std::string &key, const std::string &val) {
    auto connection = redis_connections_pool_->getConnection();
    if (!connection) {
        ERROR("connection pool failed to obtain connection");
        return false;
    }
    redisReply *reply = static_cast<redisReply *>(
        redisCommand(connection, "set %s %s", key.c_str(), val.c_str()));
    // Defer defer([this, &connection, &reply]() {
    //     // freeReplyObject(reply); // when reply is not null
    //     redisFree(connection);
    // });
    if (!reply || reply->type == REDIS_REPLY_ERROR) {
        if (reply) {
            freeReplyObject(reply);
            return false;
        }
    }
}

bool RedisManager::lpush(const std::string &key, const std::string &val) {

}

bool RedisManager::rpush(const std::string &key, const std::string &val) {

}

bool RedisManager::lpop(const std::string &key, std::string &val) {

}

bool RedisManager::rpop(const std::string &key, std::string &val) {

}

bool RedisManager::hget(const std::string &key, const std::string &hkey,
                        std::string &hval) {

}

bool RedisManager::hset(const std::string &key, const std::string &hkey,
                        const std::string &hval) {

}


bool RedisManager::del(const std::string &key) {

}

bool RedisManager::exists(const std::string &key) {

}

RedisManager::RedisManager() {
    std::size_t pool_size = 5;
    std::string host = "127.0.0.1";
    int port = 6379;
    std::string user = "default";
    std::string pass = "3215";
    redis_connections_pool_ = std::make_unique<RedisConnectionPool>(
        pool_size, host, port, user, pass);
}