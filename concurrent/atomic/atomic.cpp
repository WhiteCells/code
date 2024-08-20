#include <atomic>

std::atomic_flag flag1(false);
std::atomic_flag flag2 = ATOMIC_FLAG_INIT;
std::atomic_bool flag3 {false};
std::atomic<bool> flag4 {false};

int main(int argc, char *argv[]) {

    return 0;
}