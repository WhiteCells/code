#include <mysql/mysql.h>
#include <assert.h>
#include <iostream>

// g++ -lmysqlclient mysql.cpp -o app

int main() {
    MYSQL *sql = mysql_init(nullptr);
    assert(sql);
    const char *host = "localhost";
    const char *user = "root";
    const char *pwd = "3215";
    const char *db_name = "webserver";
    int port = 3206;
    sql = mysql_real_connect(
        sql, host, user, pwd, db_name, port, nullptr, 0
    );
    assert(sql);

    // insert
    
    // drop

    // alert

    // query
    // 返回 0 成功，非 0 失败
    if (mysql_query(sql, "select * from user") == 0) {
        MYSQL_RES *res = mysql_store_result(sql);
        if (res) {
            int num_fields = mysql_num_fields(res);

            while (MYSQL_ROW row = mysql_fetch_row(res)) {
                for(int i = 0; i < num_fields; i++) {
                    std::cout << (row[i] ? row[i] : "NULL") << '\t';
                }
                std::cout << std::endl;
            }
        }
        mysql_free_result(res);
    } else {
        std::cerr << "MySQL query failed: " << mysql_error(sql) << std::endl;
    }

    // close
    mysql_close(sql);

    return 0;
}