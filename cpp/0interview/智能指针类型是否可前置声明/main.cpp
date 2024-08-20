#include <iostream>
#include <memory>

// 智能指针所包含的类型不能使用前置声明
// 智能指针使用 RAII 技术
// 需要知道对象的完整大小以分配和释放内存
// 前置声明仅告诉编译器类型存在，但不提供大小信息
class Pool;

class Worker {
public:
    Worker() {
        pool1_ = std::make_shared<Pool>();
        pool2_ = std::make_unique<Pool>();
    }

    ~Worker() {
        pool1_->close(); // error
        pool2_->close(); // error
    }

private:
    std::shared_ptr<Pool> pool1_;
    std::unique_ptr<Pool> pool2_;
};

class Pool {
public:
    void close() {}
};


int main(int argc, char *argv[]) {
    Worker worker;
    return 0;
}