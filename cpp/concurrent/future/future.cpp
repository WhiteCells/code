#include <future>

int main(int argc, char *argv[]) {
    std::future<int> res = std::async([]() -> int {
        return 0;
    });
    res.get();
    return 0;
}