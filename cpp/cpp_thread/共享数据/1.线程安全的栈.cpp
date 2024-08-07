#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <thread>
#include <iostream>

struct EmptyStackException : std::exception {
    const char *what() const throw() {
        return "empty stack";
    }
};

template<typename T>
class ThreadsafeStack {
public:
    ThreadsafeStack() : stack_(std::stack<T>()) {

    }

    ThreadsafeStack(const ThreadsafeStack &other) {
        std::lock_guard<std::mutex> lock(other.mtx_);
        stack_ = other.stack_;
    }

    ThreadsafeStack &operator=(const ThreadsafeStack &) = delete;

    void push(T new_val) {
        std::lock_guard<std::mutex> lock(mtx_);
        stack_.push(new_val);
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (stack_.empty()) {
            throw EmptyStackException();
        }
        const std::shared_ptr<T> res(std::make_shared<T>(stack_.top()));
        stack_.pop();
        return res;
    }

    void pop(T &val) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (stack_.empty()) {
            throw EmptyStackException();
        }
        val = stack_.top();
        stack_.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return stack_.empty();
    }

private:
    mutable std::mutex mtx_;
    std::stack<T> stack_;
};

int main(int argc, char *argv[]) {
    ThreadsafeStack<int> st;

    std::thread t1([&] {
        st.push(1);
        try {
            std::shared_ptr<int> ptr = st.pop();
        } catch (const EmptyStackException &e) {
            std::cout << e.what() << std::endl;
        }
    });

    t1.join();
    std::thread t2([&] {
        try {
            std::shared_ptr<int> ptr = st.pop();
        } catch (const EmptyStackException &e) {
            std::cout << e.what() << std::endl;
        }
    });

    t2.join();
    return 0;
}