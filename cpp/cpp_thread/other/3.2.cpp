#include <thread>
#include <iostream>

class Data {
public:
    void foo() {}
private:
    int a_;
};

class DataWrapper {
public:
    template<typename Func>
    void processData(Func func) {
        std::lock_guard<std::mutex> guard(mtx_);
        func(data_); // 传递了保护的数据
    }

private:
    std::mutex mtx_;
    Data data_;
};

Data *data;

void func(Data &protected_data) {
    data = &protected_data;
}

int main(int argc, char *argv[]) {
    DataWrapper wraper;
    wraper.processData(func);
    data->foo();
    return 0;
}