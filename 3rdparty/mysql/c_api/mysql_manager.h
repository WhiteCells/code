#ifndef _MYSQL_MANAGER_H_
#define _MYSQL_MANAGER_H_

#include "mysql_connect_pool.h"

class MysqlManager {
public:
    ~MysqlManager();
    static MysqlManager *getInstance();
    /**
     * int mysql_query(MYSQL *mysql, const char *q)
     */
    bool query(const std::string &query_str);

private:
    MysqlManager();
    std::unique_ptr<MysqlConnectPool> mysql_connect_pool_;
};

#endif // _MYSQL_MANAGER_H_