#include "mysql_connect_pool.h"
#include <chrono>

MysqlConnectPool::MysqlConnectPool(
    std::size_t pool_size,
    const std::string &url,
    const std::string &user,
    const std::string &pass,
    const std::string &schema) :
    pool_size_(pool_size),
    url_(url),
    user_(user),
    pass_(pass),
    schema_(schema) {

    try {
        for (std::size_t i = 0; i < pool_size_; ++i) {
            sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
            sql::Connection *connect = driver->connect(url_, user_, pass_);
            connect->setSchema(schema_);
            auto curr_time = std::chrono::system_clock::now().time_since_epoch();
            long long timestamp = std::chrono::duration_cast<std::chrono::seconds>(curr_time).count();
            connections_.push(std::make_unique<SQLConnection>(connect, timestamp));
        }
    } catch (const sql::SQLException &e) {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

MysqlConnectPool::~MysqlConnectPool() {
    std::lock_guard<std::mutex> lock(mutex_);
    while (!connections_.empty()) {
        connections_.pop();
    }
}

std::unique_ptr<SQLConnection> MysqlConnectPool::getConnect() {
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this]() {
        if (has_stop_) {
            return true;
        }
        return !connections_.empty();
    });
    if (has_stop_) {
        return nullptr;
    }
    auto connect = std::move(connections_.front());
    connections_.pop();
    return connect;
}

void MysqlConnectPool::recycleConnect(std::unique_ptr<SQLConnection> connection) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (has_stop_) {
        return;
    }
    connections_.push(std::move(connection));
    condition_.notify_one();
}

void MysqlConnectPool::stopAllConnect() {
    std::lock_guard<std::mutex> lock(mutex_);
    has_stop_ = true;
    condition_.notify_all();
}