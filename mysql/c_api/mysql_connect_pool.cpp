#include "mysql_connect_pool.h"
#include <iostream>

MysqlConnectPool::MysqlConnectPool(std::size_t pool_size,
                                   const char *host,
                                   const char *user,
                                   const char *pass,
                                   const char *db_name,
                                   unsigned int port,
                                   const char *unix_socket,
                                   unsigned long clientflag) :
    has_stop_(false) {

    for (std::size_t i = 0; i < pool_size; ++i) {
        MYSQL *sql = mysql_init(nullptr);
        sql = mysql_real_connect(sql, host, user, pass, db_name, port, unix_socket, clientflag);
        if (!sql) {
            std::cout << "sql connect failed" << std::endl;
            --i;
            continue;
        }
        connects_.push(sql);
    }
}

MysqlConnectPool::~MysqlConnectPool() {
    std::lock_guard<std::mutex> lock(mutex_);
    while (!connects_.empty()) {
        MYSQL *connect = connects_.front();
        mysql_close(connect);
        connects_.pop();
    }
}

MYSQL *MysqlConnectPool::getConnect() {
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this]() {
        if (has_stop_) {
            return true;
        }
        return !connects_.empty();
    });
    if (has_stop_) {
        return nullptr;
    }
    MYSQL *connect = connects_.front();
    connects_.pop();
    condition_.notify_one();
    return connect;
}

void MysqlConnectPool::recycleConnect(MYSQL *connect) {
    std::lock_guard<std::mutex> lock(mutex_);
    connects_.push(connect);
    condition_.notify_one();
}

void MysqlConnectPool::stopAllConnect() {
    std::lock_guard<std::mutex> lock(mutex_);
    has_stop_ = true;
    condition_.notify_all();
}
