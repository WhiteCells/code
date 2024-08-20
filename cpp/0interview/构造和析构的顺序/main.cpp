#include <iostream>

class Node {
public:
    Node() { std::cout << "Node()" << std::endl; }
    ~Node() { std::cout << "~Node()" << std::endl; }
};

class HeadNode : public Node {
public:
    HeadNode() { std::cout << "HeadNode()" << std::endl; }
    ~HeadNode() { std::cout << "~HeadNode()" << std::endl; }
};

class Session {
public:
    Session() { std::cout << "Session()" << std::endl; }
    ~Session() { std::cout << "~Session()" << std::endl; }

private:
    Node node;
};

int main(int argc, char *argv[]) {
    {
        HeadNode node;
    }
    std::cout << "------" << std::endl;
    {
        Session session;
    }
    return 0;
}