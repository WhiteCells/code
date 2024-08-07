#include <iostream>
/*
        std::cerr << __func__ << " " << __LINE__                \
                  << " ERROR: " << buf << std::endl;            \

 */
#define ERROR(format, ...)                                      \
    do {                                                        \
        char buf[1024] {0};                                     \
        snprintf(buf, 1024, format, ##__VA_ARGS__);             \
        printf("%s %d ERROR: %s\n", __func__, __LINE__, buf);   \
    } while (0)                                                 \

int main(int argc, char *argv[]) {
    int error_code = 404;
    ERROR("An error occurred: code %d", error_code);
    return 0;
}