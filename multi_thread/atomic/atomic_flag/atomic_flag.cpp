#include <atomic>

std::atomic_flag flag1(false);
std::atomic_flag flag2 = ATOMIC_FLAG_INIT;

// std::atomic_flag flag3 = false; // error

int main(int argc, char *argv[]) {

    return 0;
}