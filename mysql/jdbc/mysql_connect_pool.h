#ifndef _MYSQL_CONNECT_POOL_H_
#define _MYSQL_CONNECT_POOL_H_

#include <jdbc/mysql_driver.h>
#include <memory>
#include <string>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>

struct SQLConnection {
    SQLConnection(sql::Connection *connect, int64_t last_oper_time) :
        connect_(connect),
        last_oper_time_(last_oper_time) {
    }
    std::unique_ptr<sql::Connection> connect_;
    int64_t last_oper_time_;
};

class MysqlConnectPool {
public:
    MysqlConnectPool(
        std::size_t pool_size,
        const std::string &url,
        const std::string &user,
        const std::string &pass,
        const std::string &schema);
    ~MysqlConnectPool();
    std::unique_ptr<SQLConnection> getConnect();
    void recycleConnect(std::unique_ptr<SQLConnection> connection);
    void stopAllConnect();

private:
    std::size_t pool_size_;
    std::string url_;
    std::string user_;
    std::string pass_;
    std::string schema_;
    std::mutex mutex_;
    std::atomic_bool has_stop_;
    std::condition_variable condition_;
    std::queue<std::unique_ptr<SQLConnection>> connections_;
};

#endif // _MYSQL_CONNECT_POOL_H_