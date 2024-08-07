#include <iostream>

class show_id {
public:
    ~show_id() { std::cout << id; }
    int id;
};

int main() {
    delete[] new show_id[3]{ { 0 }, { 1 }, { 2 } }; // 2 1 0

    show_id* id = new show_id();
    delete id; // 0
}