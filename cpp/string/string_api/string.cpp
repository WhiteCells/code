#include <iostream>
#include <vector>

#include <string>

void UseString() {
    std::string s;
    s += 'c';
    s.append("s");
    s.append("a");
    s.append("D");

    std::cout << s << '\n'; // cpp

    const char* c_str = s.c_str();
    for (const char* p = c_str; *p != '\0'; ++p) {
        printf("%c", *p); // c
    }
    printf("\n");
    printf("%s\n", c_str); // c

    int a = 1;
    // s.append(a); // append 参数 string
    s.push_back(a + '0');
    std::cout << s << '\n';
    std::string s1 = "123";
    std::string s2 = "11";
    const char* s3 = "123";
    std::cout << std::to_string(atoi(s1.c_str()) + atoi(s2.c_str()) + atoi(s3));

    // string clear
    s.clear();
    s = "";
}


void StringReadRow() {
    std::string s;
    std::getline(std::cin, s); // read a row
    std::cout << s << '\n';
}


void StringType() {
    std::string s { "hello" };
    std::cout << typeid(s[0]).name() << ' ' << typeid(char).name() << '\n';
}

void StringFind() {
    std::string s { "test*/int a" };
    std::string s2;
    if (s.find("*/") != std::string::npos) {
        s2 = std::string(s.begin() + s.find("*/") + 2, s.end());
    }
    std::cout << s2 << '\n';
    // if (s[0] == s[3] == 't') { // ?
    //     std::cout << "1" << '\n';
    // }
    if (s[0] == s[3]) {
        std::cout << "2" << '\n';
    }
    if ('t' == s[0] && 't' == s[3]) {
        std::cout << "3" << '\n';
    }
}

void InterceptString() {
    std::string s = "hello";
    if ("hel" == std::string(s.begin(), s.begin() + 3)) {
        std::cout << "1" << '\n';
    }
}

void StringChar() {
    std::string str;
    std::string s2 = "->";
    // char a = 'a', b = 'b';
    int a = 1, b = 2;

    // char s = (a + '0'), e = (b + '0');
    // str += s + s2 + e;

    str += std::to_string(a) + "->" + std::to_string(b);
    std::cout << str << '\n';
}

void Stringtest() {
    std::string s = "abc";
    std::string s2 = std::string(s.begin(), s.begin()); // [)
    std::cout << s2 << '\n';
}

int main() {
    // UseString();
    // StringReadRow();
    // StringType();
    // StringFind();
    // InterceptString();
    // StringChar();
    // Stringtest();

    std::string str = "hello";
    std::cout << str.data() << std::endl;
    return 0;
}