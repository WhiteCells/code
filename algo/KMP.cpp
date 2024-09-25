#include <iostream>
#include <vector>
#include <string>

void getNext(
    const std::string &str,
    std::vector<int> &next)
{
    int n = str.size();
    int i = 1, j = 0;
    next[0] = 0;
    while (i < n) {
        if (j == 0 || str[i] == str[j]) {
            ++i;
            ++j;
            next[i] = j;
        }
        else {
            j = next[i];
        }
    }
}

bool KMP(
    const std::string &main_str,
    const std::string &sub_str,
    const std::vector<int> &next)
{
    int i = 0, j = 0;
    int n = sub_str.size();
    while (i < n) {
        if (main_str[i] == sub_str[j]) {
            ++j;
        }
        else {
            j = next[i];
        }
        ++i;
    }
    return i == j;
}

int main(int argc, char *argv[])
{
    std::string main_str = "abcabac";
    std::string sub_str = "aba";
    std::vector<int> next(main_str.size());
    getNext(main_str, next);
    std::cout << KMP(main_str, sub_str, next) << std::endl;
    return 0;
}