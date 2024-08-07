namespace a {
namespace b {
class X {};
}
}

namespace c = a::b;
using x = c::X;

int main(int argc, char *argv[]) {
    x x1;
    return 0;
}