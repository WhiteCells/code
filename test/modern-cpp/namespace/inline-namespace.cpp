#include <iostream>

namespace Parent {
    namespace V1 {
        void foo() { std::cout << "foo v1.0" << std::endl; }
    }
    namespace V2 {
        void foo() { std::cout << "foo v2.0" << std::endl; }
    }
    inline namespace V3 { // latest version
        void foo() { std::cout << "foo v3.0" << std::endl; }
    }
}

void test1() {
    Parent::foo();
    Parent::V1::foo(); // old version
}

namespace n1
{
    namespace A::B::C {
        void foo() { std::cout << "A::B::C::foo" << std::endl; }
    }

    // namespace A {
    //     namespace B {
    //         namespace C {
    //             void foo() { std::cout << "A::B::C::foo" << std::endl; }
    //         }
    //     }
    // }
} // namespace n1


namespace n2
{
    namespace A::B::inline C {
        void foo() { std::cout << "A::B::foo" << std::endl; }
    }

    // namespace A::B {
    //     inline namespace C {
    //         void foo() { std::cout << "A::B::foo" << std::endl; }
    //     }
    // }
} // namespace n2

namespace n3
{
    namespace A::inline B::C {
        void foo() { std::cout << "A::C::foo" << std::endl; }
    }

    // namespace A {
    //     inline namespace B {
    //         namespace C {
    //             void foo() { std::cout << "A::C::foo" << std::endl; }
    //         }
    //     }
    // }
} // namespace n3

int main() {
}