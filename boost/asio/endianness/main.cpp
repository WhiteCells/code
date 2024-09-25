#include <boost/asio.hpp>
#include <arpa/inet.h>
#include <iostream>

namespace asio = boost::asio;

int main(int argc, char *argv[]) {
    short len1 = 10;
    len1 = htons(len1);
    short asio_local_len1 = asio::detail::socket_ops::network_to_host_short(len1);
    short posix_local_len1 = ntohs(len1);

    std::cout << asio_local_len1 << std::endl;
    std::cout << posix_local_len1 << std::endl;

    short len2 = 10;
    len2 = asio::detail::socket_ops::host_to_network_short(len2);
    short asio_local_len2 = asio::detail::socket_ops::network_to_host_short(len2);
    short posix_local_len2 = ntohs(len2);

    std::cout << asio_local_len2 << std::endl;
    std::cout << posix_local_len2 << std::endl;

    return 0;
}