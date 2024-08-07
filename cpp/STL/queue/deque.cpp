#include <iostream>

#include <deque>


void UseDeque() {
    std::deque<int> q;
    q.push_back(1);
    std::cout << q.front() << '\n';
}


int main() {
    UseDeque();
    return 0;
}