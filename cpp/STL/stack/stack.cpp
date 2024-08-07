#include <iostream>

#include <stack>


void UseStack() {
    std::stack<int> s; // 不能聚合初始化

    s.push(10);

    std::cout << "s.size() = " << s.size() << '\n'; // 访问栈长度
    std::cout << "s.top() = " << s.top() << '\n';   // 访问栈顶 10

    if (!s.empty()) {
        s.pop(); // 弹出栈顶，栈非空才弹出栈顶
    }
    if (!s.empty()) {
        std::cout << s.top() << '\n'; // 栈非空才访问栈顶，否则 Segmentation fault
    }
}

void EmptyStack() {
    std::stack<int> s;
    std::cout << s.size() << ' ' << s.empty() << '\n'; // 0 1
    
    s.pop(); // Illegal operation
    std::cout << s.size() << ' ' << s.empty() << '\n'; // 18446744073709551615 0
    s.pop();
    std::cout << s.size() << ' ' << s.empty() << '\n'; // 18446744073709551614 0
    s.pop();
    std::cout << s.size() << ' ' << s.empty() << '\n'; // 18446744073709551613 0
    s.pop();
    std::cout << s.size() << ' ' << s.empty() << '\n'; // 18446744073709551612 0
}

int main() {
    UseStack();
    EmptyStack();
    return 0;
}