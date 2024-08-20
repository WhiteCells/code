#include <iostream>

/**
 * error case
 */
class Node {
public:
    Node(int len, int total_len) :
        len_(len),
        total_len_(total_len + len_) {
            
        std::cout << "parameter: len: " << len << std::endl;
        std::cout << "argument : slen_: " << len_ << std::endl;
        std::cout << "parameter: total_len: " << total_len << std::endl;
        std::cout << "argument : total_len_: " << total_len_ << std::endl;
    }
private:
    int total_len_;
    int len_;
};

int main(int argc, char *argv[]) {
    Node(1, 10);
    return 0;
}