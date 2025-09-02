#include "mysql_manager.h"

int main(int argc, char *argv[]) {
    MysqlManager::getInstance()->registerUser("user1", "xxx@qq.com", "pass", "icon1");
    return 0;
}