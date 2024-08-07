#ifndef _REDIS_MANAGER_H_
#define _REDIS_MANAGER_H_

#include "singleton.hpp"
#include "redis_connection_pool.h"
#include <hiredis/hiredis.h>
#include <string>
#include <iostream>

class RedisManager :
    public Singleton<RedisManager> {
    friend class Singleton<RedisManager>;

public:
    /// @brief 
    ~RedisManager();

    /// @brief 
    /// @param key 
    /// @param val 
    /// @return 
    bool get(const std::string &key, std::string &val);

    /// @brief 
    /// @param key 
    /// @param val 
    /// @return 
    bool set(const std::string &key, const std::string &val);

    /// @brief 
    /// @param key 
    /// @param val 
    /// @return 
    bool lpush(const std::string &key, const std::string &val);

    /// @brief 
    /// @param key 
    /// @param val 
    /// @return 
    bool rpush(const std::string &key, const std::string &val);

    /// @brief 
    /// @param key 
    /// @param val 
    /// @return 
    bool lpop(const std::string &key, std::string &val);

    /// @brief 
    /// @param key 
    /// @param val 
    /// @return 
    bool rpop(const std::string &key, std::string &val);

    /// @brief 
    /// @param key 
    /// @param hkey 
    /// @param hval 
    /// @return 
    bool hget(const std::string &key, const std::string &hkey,
              std::string &hval);

    /// @brief 
    /// @param key 
    /// @param hkey 
    /// @param hval 
    /// @return 
    bool hset(const std::string &key, const std::string &hkey,
              const std::string &hval);

    /// @brief 
    /// @param key 
    /// @return 
    bool del(const std::string &key);

    /// @brief 
    /// @param key 
    /// @return 
    bool exists(const std::string &key);

private:
    RedisManager();
    std::unique_ptr<RedisConnectionPool> redis_connections_pool_;
};

#endif // _REDIS_MANAGER_H_