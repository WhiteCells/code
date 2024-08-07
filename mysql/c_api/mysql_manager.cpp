#include "mysql_manager.h"
#include <iostream>

MysqlManager::~MysqlManager() {
    mysql_connect_pool_->stopAllConnect();
}

MysqlManager *MysqlManager::getInstance() {
    static MysqlManager mysql_manager;
    return &mysql_manager;
}

bool MysqlManager::query(const std::string &query_str) {
    MYSQL *connect = mysql_connect_pool_->getConnect();
    if (mysql_query(connect, query_str.c_str()) == 0) {
        MYSQL_RES *res = mysql_store_result(connect);
        if (res) {
            int fields_num = mysql_num_fields(res);
            MYSQL_ROW row;
            while (row = mysql_fetch_row(res)) {
                for (int i = 0; i < fields_num; ++i) {
                    std::cout << (row[i] ? row[i] : "null") << '\t';
                }
                std::cout << std::endl;
            }
            // if (row == nullptr) {
            //     mysql_connect_pool_->recycleConnect(connect);
            //     mysql_free_result(res);
            //     return false;
            // }
        }
        mysql_free_result(res);
        mysql_connect_pool_->recycleConnect(connect);
    } else {
        std::cout << mysql_error(connect) << std::endl;
        mysql_connect_pool_->recycleConnect(connect);
        return false;
    }
    return true;
}


MysqlManager::MysqlManager() {
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
    std::size_t pool_size = 5;
    const char *host = "127.0.0.1";
    const char *user = "root";
    const char *pass = "3215";
    const char *da_name = "chat_user";
    unsigned int port = 3306;
    const char *unix_socket = nullptr;
    unsigned long clientflag = 0;
    mysql_connect_pool_ = std::make_unique<MysqlConnectPool>(
        pool_size,
        host, user,
        pass,
        da_name,
        port,
        unix_socket,
        clientflag
    );
}