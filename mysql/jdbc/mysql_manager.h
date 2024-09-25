#ifndef _MYSQL_MANAGER_H_
#define _MYSQL_MANAGER_H_

#include "mysql_connect_pool.h"

struct UserInfo {
    int uid;
    std::string name;
    std::string pass;
    std::string email;
};

class MysqlManager {
public:
    ~MysqlManager();
    static std::shared_ptr<MysqlManager> getInstance();
    int registerUser(
        const std::string &name,
        const std::string &email,
        const std::string &pass,
        const std::string &icon);
    int registerTransaction(
        const std::string &name,
        const std::string &email,
        const std::string &pass,
        const std::string &iocn);
    bool checkEmail(
        const std::string &name,
        const std::string &email);
    bool updatePass(
        const std::string &name,
        const std::string &new_pass);
    bool checkPass(
        const std::string &name,
        const std::string &pass,
        UserInfo &user_info);
    bool testProcedure(
        const std::string &email,
        int &uid,
        std::string &name);

private:
    MysqlManager();
    std::unique_ptr<MysqlConnectPool> mysql_connect_pool_;
};

#endif // _MYSQL_MANAGER_H_