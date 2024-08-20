#include <iostream>
#include <fstream>
#include "login.pb.h"

using login::LoginRequest;

// int main(int argc, char *argv[]) {
//     LoginRequest request;
//     request.set_name("user1");
//     request.set_pass("pass");
//     request.set_token("xxxxx");
//     std::fstream out(
//         "login", std::ios::out
//         | std::ios::binary
//         | std::ios::trunc
//     );
//     request.SerializeToOstream(&out);
//     out.close();

//     LoginRequest request2;
//     std::fstream in(
//         "login", std::ios::in
//         | std::ios::binary
//     );
//     if (!request2.ParseFromIstream(&in)) {
//         std::cerr << "failed to parse login" << std::endl;
//         return 1;
//     }
//     std::cout << request2.name() << std::endl;
//     std::cout << request2.pass() << std::endl;
//     std::cout << request2.token() << std::endl;
//     return 0;
// }

int main(int argc, char *argv[]) {
    LoginRequest request;
    request.set_name("name1");
    request.set_pass("pass");
    std::string proto_str {};
    if (!request.SerializeToString(&proto_str)) {
        std::cerr << "serialize to string failed" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << proto_str << std::endl;

    LoginRequest request2;
    if (!request2.ParseFromString(proto_str)) {
        std::cerr << "parse from string failed" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << request2.name() << std::endl;
    std::cout << request2.pass() << std::endl;
    return 0;
}