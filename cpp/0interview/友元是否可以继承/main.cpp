#include <iostream>

class Node {
    friend void foo();
    friend class Session;

public:
    Node() : data_(new char[6] {"hello"}), len_(6) {}
    ~Node() { delete[] data_; }

protected:
    char *data_;

private:
    int len_;
};

class ReceiveNode : public Node {
public:
    ReceiveNode() {}
    ~ReceiveNode() {}

private:
    int id_;
};

class Session {
public:
    Session() {}
    ~Session() {}

    void send() {
        std::cout << receive_node_.data_ << std::endl;
        std::cout << receive_node_.len_ << std::endl;
        // std::cout << receive_node_.id_ << std::endl; // error
    }

private:
    ReceiveNode receive_node_;
};

void foo() {
    ReceiveNode receive_node_;
    std::cout << receive_node_.data_ << std::endl;
    std::cout << receive_node_.len_ << std::endl;
    // std::cout << receive_node_.id_ << std::endl; // error
}

int main(int argc, char *argv[]) {
    foo();
    return 0;
}