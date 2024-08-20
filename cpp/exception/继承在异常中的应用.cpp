#include<iostream>
using namespace std;

// 异常基类
class BaseMyException {
public:
    virtual void what() = 0; // 纯虚函数
    virtual ~BaseMyException() {} // 虚析构
};

// 目标文件异常类
class TargetSapceNullException : public BaseMyException {
public:
    // 重写父类纯虚函数
    virtual void what() {
        cout << "Target Sapce Null" << endl;
    }
    ~TargetSapceNullException() {}
};

// 源文件异常类
class SourceSpaceNullException : public BaseMyException {
public:
    // 重写父类纯虚函数
    virtual void what() {
        cout << "Source Space Null" << endl;
    }
    ~SourceSpaceNullException() {}
};

void copy_str(char *target, const char *source) {
    if (!target) {
        throw TargetSapceNullException();
    }
    if (!source) {
        throw SourceSpaceNullException();
    }
    while (*source != '\0') {
        *target = *source;
        target++;
        source++;
    }
}

int main() {
    const char *source = "hello";
    char buf[1024] = {0};
    try {
        copy_str(buf, NULL);
        cout << buf << endl;
    } catch (BaseMyException &e) {
        e.what();
    }
    return 0;
}