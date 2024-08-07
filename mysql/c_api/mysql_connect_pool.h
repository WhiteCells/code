#ifndef _MYSQL_CONNECT_POOL_H_
#define _MYSQL_CONNECT_POOL_H_

#include <mysql/mysql.h>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <string>

class MysqlConnectPool {
public:
    /**
     * MYSQL *mysql_real_connect(
     *     MYSQL *mysql,
     *     const char *host,
     *     const char *user,
     *     const char *passwd,
     *     const char *db,
     *     unsigned int port,
     *     const char *unix_socket,
     *     unsigned long clientflag
     * );
     */
    MysqlConnectPool(std::size_t pool_size,
                     const char *host,
                     const char *user,
                     const char *pass,
                     const char *db_name,
                     unsigned int port,
                     const char *unix_socket,
                     unsigned long clientflag);
    ~MysqlConnectPool();
    MYSQL *getConnect();
    void recycleConnect(MYSQL *connect);
    void stopAllConnect();

private:
    std::size_t pool_size_;
    std::atomic<bool> has_stop_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::queue<MYSQL *> connects_;
};

#endif // _MYSQL_CONNECT_POOL_H_