#include "mysql_manager.h"
#include <jdbc/cppconn/prepared_statement.h>

MysqlManager::~MysqlManager() {
}

std::shared_ptr<MysqlManager> MysqlManager::getInstance() {
    static std::shared_ptr<MysqlManager> mysql_manager(new MysqlManager());
    return mysql_manager;
}

int MysqlManager::registerUser(
    const std::string &name,
    const std::string &email,
    const std::string &pass,
    const std::string &icon) {

    auto connect = mysql_connect_pool_->getConnect();
    try {
        if (connect == nullptr) {
            return false;
        }
        std::unique_ptr<sql::PreparedStatement> stmt(
            connect->connect_->prepareStatement(
                "CALL reg_user(?,?,?,@result)"));
        stmt->setString(1, name);
        stmt->setString(2, email);
        stmt->setString(3, pass);
        stmt->execute();
        std::unique_ptr<sql::Statement> stmt_result(
            connect->connect_->createStatement());
        std::unique_ptr<sql::ResultSet> result(
            stmt_result->executeQuery("SELECT @result AS result"));
        if (result->next()) {
            int res = result->getInt("result");
            std::cout << "result: " << res << std::endl;
            mysql_connect_pool_->recycleConnect(std::move(connect));
            return res;
        }
        mysql_connect_pool_->recycleConnect(std::move(connect));
        return -1;
    } catch (sql::SQLException &exception) {
        mysql_connect_pool_->recycleConnect(std::move(connect));
        std::cerr << "SQLException: " << exception.what() << std::endl;
        std::cerr << "Error Code: " << exception.getErrorCode() << std::endl;
        std::cerr << "SQL State: " << exception.getSQLState() << std::endl;
        return -1;
    }
}

int MysqlManager::registerTransaction(
    const std::string &name,
    const std::string &email,
    const std::string &pass,
    const std::string &iocn) {

    auto connect = mysql_connect_pool_->getConnect();
    if (connect) {
        return false;
    }
}

bool MysqlManager::checkEmail(
    const std::string &name,
    const std::string &email) {
}

bool MysqlManager::updatePass(
    const std::string &name,
    const std::string &new_pass) {
}

bool MysqlManager::checkPass(
    const std::string &name,
    const std::string &pass,
    UserInfo &user_info) {
}

bool MysqlManager::testProcedure(
    const std::string &email,
    int &uid,
    std::string &name) {
}

MysqlManager::MysqlManager() {
    std::size_t pool_size = 5;
    std::string url = "127.0.0.1:3306";
    std::string user = "root";
    std::string pass = "3215";
    std::string schema = "chat_user";
    mysql_connect_pool_ = std::make_unique<MysqlConnectPool>(5, url, user, pass, schema);
}