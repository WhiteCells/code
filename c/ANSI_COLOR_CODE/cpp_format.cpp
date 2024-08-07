#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <cstdio>
#include <memory>
#include <cstdarg>

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

inline std::string string_format(const std::string& format, ...) {
    va_list args;
    va_start(args, format);
    size_t size = std::vsnprintf(nullptr, 0, format.c_str(), args) + 1;
    va_end(args);

    std::unique_ptr<char[]> buf(new char[size]);
    va_start(args, format);
    std::vsnprintf(buf.get(), size, format.c_str(), args);
    va_end(args);

    return std::string(buf.get(), buf.get() + size - 1);
}

#define WARN(format, ...)                           \
    do {                                            \
        std::ostringstream oss;                     \
        oss << ANSI_COLOR_YELLOW                    \
            << "[WARN ] [" << __func__ << "]: "     \
            << string_format(format, ##__VA_ARGS__) \
            << ANSI_COLOR_RESET << std::endl;       \
        std::cout << oss.str();                     \
    } while (0)

int main(int argc, char *argv[]) {
    WARN("This is a warning message with number: %d", 42);
    WARN("This is another warning message");
    return 0;
}