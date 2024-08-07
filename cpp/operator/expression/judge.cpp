#include <iostream>

void test() {
    int arr[100];
    for (int i = 0; i < 100; ++i) {
        arr[i] = i + 1;
    }
    for (int i = 0; i < 100; ++i) {
        if (45 <= arr[i] <= 55) { // (45 <= arr[i]) <= 55
        // if (arr[i] >= 45 && arr[i] <= 55) {
            std::cout << arr[i] << ' ';
        }
    }
}

int main() {
    test();
    return 0;
}