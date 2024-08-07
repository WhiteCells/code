#include <stdio.h>
#include <iostream>

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"

int main(int argc, char *argv[]) {
    printf(ANSI_COLOR_GREEN "INFO\n" ANSI_COLOR_RESET);
    std::cout << ANSI_COLOR_RED << "WARNING" << ANSI_COLOR_RESET << std::endl;
    return 0;
}