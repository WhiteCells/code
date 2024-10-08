#include <iostream>

void cplusplus() {
#ifdef __cplusplus
    switch (__cplusplus) {
        case 202002L:
            std::cout << "C++20" << std::endl;
            break;
        case 201703L:
            std::cout << "C++17" << std::endl;
            break;
        case 201402L:
            std::cout << "C++14" << std::endl;
            break;
        case 201103L:
            std::cout << "C++11" << std::endl;
            break;
        case 199711L:
            std::cout << "C++98" << std::endl;
            break;
        default:
            std::cout << "Pre-standard C++" << std::endl;
            break;
    }
#endif
}

/*
    Windows 系统：
        _WIN32: 在 32 位和 64 位 Windows 系统上都会被定义。
        _WIN64: 仅在 64 位 Windows 系统上被定义。
    Unix 和类 Unix 系统：
        __unix__: 在 Unix 和类 Unix 系统（如 Linux）上被定义。
        __APPLE__: 在 macOS 和 iOS 系统上被定义。
        __linux__: 在 Linux 系统上被定义。
        __FreeBSD__: 在 FreeBSD 系统上被定义。
        __OpenBSD__: 在 OpenBSD 系统上被定义。
        __NetBSD__: 在 NetBSD 系统上被定义。
        __DragonFly__: 在 DragonFly BSD 系统上被定义。
        __sun: 在 Solaris 系统上被定义。
        __hpux: 在 HP-UX 系统上被定义。
        __sgi: 在 IRIX 系统上被定义。
        __AIX: 在 AIX 系统上被定义。
    其他：
        __ANDROID__: 在 Android 平台上被定义。
        __CYGWIN__: 在 Cygwin 环境下被定义。
        __MINGW32__: 在 MinGW 32 位编译环境下被定义。
        __MINGW64__: 在 MinGW 64 位编译环境下被定义。
 */

void foo() {
    
#ifdef _WIN64
    // 64 位 Windows 系统上，_WIN32 和 _WIN64 都会被定义，需要先判断 _WIN64
    std::cout << "Windows 64 bits" << std::endl;
#elif _WIN32
    // 如果 _WIN64 没有被定义，此时再判断 _WIN32 是否被定义
    std::cout << "Windows 32 bits" << std::endl;
#else
    std::cout << "Not a Windows System" << std::endl;
#endif

#if defined(__unix__) || defined(__APPLE__)
    std::cout << "This is a Unix or Unix-like system." << std::endl;
#else
    std::cout << "This is not a Unix or Unix-like system." << std::endl;
#endif

    // 用于指示编译器是否遵循 C 标准。如果编译器遵循 C 标准，则该宏的值为 1；否则，该宏未定义。
    std::cout << __STDC__             << std::endl;

    // 用于指示编译器是否正在编译 C++ 代码。如果编译器正在编译 C++ 代码，则该宏的值为一个非零值；否则，该宏未定义。
    std::cout << __cplusplus          << std::endl;

    // 用于获取当前函数的名称作为一个字符串常量。它在 C++11 标准中引入
    std::cout <<  __func__            << std::endl;

    // 用于获取当前函数的名称作为一个字符串常量。它在一些编译器中可用，但不是标准的 C++ 宏
    std::cout <<  __FUNCTION__        << std::endl;

    // 用于获取当前函数的名称，并包含了更详细的信息，如参数类型和返回类型。它在某些编译器中可用，但不是标准的 C++ 宏
    std::cout <<  __PRETTY_FUNCTION__ << std::endl;

    // 用于获取当前源文件的名称作为一个字符串常量
    std::cout <<  __FILE__            << std::endl;

    // 用于获取当前代码行号
    std::cout <<  __LINE__            << std::endl;

    // 用于获取当前编译日期，以字符串常量的形式表示
    std::cout <<  __DATE__            << std::endl;

    // 用于获取当前编译时间，以字符串常量的形式表示
    std::cout <<  __TIME__            << std::endl;

    // 用于获取当前编译时间戳，以字符串常量的形式表示
    std::cout <<  __TIMESTAMP__       << std::endl;
}

int main(int argc, char const *argv[]) {
    foo();
    cplusplus();
    return 0;
}