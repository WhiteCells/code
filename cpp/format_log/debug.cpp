#include <iostream>
#include <sstream>

// 定义一个辅助函数模板来打印错误消息
template<typename... Args>
void PrintError(const std::string& func, int line, const std::string& msg, Args... args) {
    std::ostringstream oss;
    oss << func << " " << line << " ERROR: " << msg;
    ((oss << " " << args), ...);
    std::cerr << oss.str() << std::endl;
}

// 定义一个宏来调用辅助函数
#define ERROR(msg, ...) PrintError(__func__, __LINE__, msg, ##__VA_ARGS__)

// 示例使用
void someFunction() {
    int errorCode = 404;
    ERROR("Failed with error code: ", errorCode); // 注意这里没有使用{}或%d
}

int main() {
    someFunction();
    return 0;
}