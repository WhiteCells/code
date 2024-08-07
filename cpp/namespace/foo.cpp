#include "foo.h"

using namespace A;

void A::foo() {
    std::cout << "test" << std::endl;
}

Route::Route() {
    std::cout << "Route" << std::endl;
}

int main(int argc, char *argv[]) {
    foo();
    Route r;
    return 0;
}