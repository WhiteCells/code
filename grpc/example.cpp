#include <iostream>
#include <fstream>
#include "message.pb.h"

int main(int argc, char *argv[]) {
    smart::test msg1;
    msg1.set_age(101);
    msg1.set_name("aaa");
    msg1.set_email("aaa@bb.cc");
    std::fstream out("user.pb", std::ios::out
                     | std::ios::binary
                     | std::ios::trunc);
    msg1.SerializeToOstream(&out);
    out.close();

    smart::test msg2;
    std::fstream in("user.pb", std::ios::in
                    | std::ios::binary);
    if (!msg2.ParseFromIstream(&in)) {
        std::cerr << "failed to parse user.pb" << std::endl;
        return 1;
    }
    std::cout << msg2.age() << std::endl;
    std::cout << msg2.name() << std::endl;
    std::cout << msg2.email() << std::endl;
    return 0;
}