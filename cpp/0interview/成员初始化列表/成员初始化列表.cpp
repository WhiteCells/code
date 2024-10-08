#include <iostream>
#include <vector>

class IoContextPool {
public:
    IoContextPool() : vec_ {1,2,3} {}

    IoContextPool(int) : vec_ {3} {}

    IoContextPool(int, int) : vec_(3) {}

    void print() {
        for (const auto &item : vec_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<int> vec_;
};

int main(int argc, char *argv[]) {
    IoContextPool pool1;
    pool1.print(); // 1 2 3

    IoContextPool pool2(1);
    pool2.print(); // 3

    IoContextPool pool3(1, 1);
    pool3.print(); // 0 0 0
    return 0;
}