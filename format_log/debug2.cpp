#include <iostream>

#define ERROR(format, ...)                                                      \
    do {                                                                        \
        printf("%s:%d ERROR: " format "\n", __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)                                                                 \

int main() {
    int error_code = 404;
    ERROR("An error occurred: code %d", error_code);
    return 0;
}