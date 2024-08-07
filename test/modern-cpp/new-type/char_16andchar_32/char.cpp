#include <iostream>
#include <windows.h>
#include <cuchar>

namespace Parent {
    namespace Child1 {
        void foo();
    }
    namespace Child2 {
        void foo();
    }
}

void Parent::Child1::foo() {
    puts("Child1 foo");
}

void Parent::Child2::foo() {
    puts("Child2 foo");
}

int main(int argc, char const *argv[]) {
    char utf8c = u8'c';      // C++17
    char16_t utf16c = u'中';
    char32_t utf32c = U'文';
    char8_t utf8[] = u8"你好世界";
    char16_t utf16[] = u"你好世界";
    char32_t utf32[] = U"你好世界";

    LPCWCHAR wstr = L"你好世界";
    wchar_t wc = L'测';
    wchar_t ws[] = L"测试";

    char8_t c = u8'c';


    Parent::Child1::foo();
    Parent::Child2::foo();
    return 0;
}