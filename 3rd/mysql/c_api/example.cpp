#include "mysql_manager.h"

int main(int argc, char *argv[]) {
    MysqlManager *manager = MysqlManager::getInstance();
    manager->query("select * from user");
    return 0;
}