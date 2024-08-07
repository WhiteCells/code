#include <iostream>

void foo(int **const ptr) {
    *ptr = nullptr;
}

// void foo(int *const ptr) {

// }

// 返回指针，指针的值修改是否对指针指向的地址有影响
int *getPtr() {
    static int *ptr = new int(20);
    return ptr;
}

int main(int argc, char *argv[]) {
    int a = 10;
    int *p = &a;
    foo(&p);

    if (p != nullptr) {
        std::cout << a << std::endl;
    }

    int *ret_ptr = getPtr();
    if (ret_ptr != nullptr) {
        std::cout << *ret_ptr << std::endl;
    }

    delete ret_ptr;
    ret_ptr = nullptr;

    int *ret_ptr2 = getPtr();
    if (ret_ptr2 != nullptr) {
        std::cout << *ret_ptr2 << std::endl;
    }

    return 0;
}