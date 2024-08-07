#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <system_error>

namespace asio = boost::asio;

// 客户端生成通信的端点
// 将 ip 和 port 转换为端点
int client_end_point() {
    // 发送地址
    std::string raw_ip_address {"127.0.0.1"};
    // 发送地址的端点
    unsigned short port_num = 80;
    boost::system::error_code err_code;
    // raw ip to ip
    asio::ip::address ip_address \
        = asio::ip::address::from_string(raw_ip_address, err_code);
    if (err_code.value() != 0) {
        std::cout << "[error code]: " << err_code.value()   << std::endl;
        std::cout << "[message   ]: " << err_code.message() << std::endl;
        return err_code.value();
    }
    asio::ip::tcp::endpoint end_point(ip_address, port_num);
    return 0;
}

// 服务器生成通信的端点
int server_end_point() {
    unsigned short port_num = 80;
    // 任何 ipv4 地址都可以和服务器通信
    // 绑定服务器本地地址
    asio::ip::address ip_address \
        = asio::ip::address_v4::any();
    asio::ip::tcp::endpoint end_point(ip_address, port_num);
    return 0;
}

// 创建 socket
int create_tcp_socket() {
    // socket 需要上下文
    // asio::io_service ios; // (old version)
    asio::io_context ioc;
    // 使用上下文创建 socket
    asio::ip::tcp::socket socket(ioc);

    // 判断创建 socket 是否成功（新版本的 asio 会在创建时判断）
    boost::system::error_code err_code;
    // ipv4 协议
    asio::ip::tcp protocol = asio::ip::tcp::v4();
    socket.open(protocol, err_code);
    if (err_code.value() != 0) {
        std::cerr << "[error code]: " << err_code.value()   << std::endl;
        std::cerr << "[message   ]: " << err_code.message() << std::endl;
        return err_code.value();
    }
    return 0;
}

// 服务器绑定端点
int server_create_acceptor_socket() {
    asio::io_context ioc;
    asio::ip::tcp::acceptor acceptor(ioc);

    // 判断创建 acceptor 是否成功（较新版本 asio 会在创建时判断）
    boost::system::error_code err_code;
    asio::ip::tcp protocol = asio::ip::tcp::v4();
    acceptor.open(protocol, err_code);
    if (err_code.value() != 0) {
        std::cerr << "[error code]: " << err_code.value()   << std::endl;
        std::cerr << "[message   ]: " << err_code.message() << std::endl;
        return err_code.value();
    }
    return 0;

    /* new version */
    unsigned short port_num = 80;
    // 接受所有 ipv4 地址并且发往指定端口的连接
    asio::ip::tcp::endpoint end_point(asio::ip::tcp::v4(), port_num);
    // 底层绑定端点
    asio::ip::tcp::acceptor acceptor2(
        ioc,
        end_point
        // asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port_num)
    );
}

// 服务器绑定端点
int bind_acceptor_socket() {
    unsigned short port_num = 80;
    asio::ip::tcp::endpoint end_point(asio::ip::address_v4::any(), port_num);
    asio::io_context ioc;
    asio::ip::tcp::acceptor acceptor(
        ioc,
        end_point.protocol()
        // asio::ip::tcp::v4()
    );
    // 手动绑定端点
    boost::system::error_code err_code;
    acceptor.bind(end_point, err_code);
    if (err_code.value() != 0) {
        std::cerr << "[error code]: " << err_code.value()   << std::endl;
        std::cerr << "[bind error]: " << err_code.what()    << std::endl;
        std::cerr << "[message   ]: " << err_code.message() << std::endl;
        return err_code.value();
    }
    return 0;
}

// 对于客户端是 connect，对于服务器是 bind
int client_connect_to_end_point() {
    // 服务器 ip
    std::string raw_ip_address {"127.0.0.1"};
    asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address);
    // 服务器 port
    // asio::ip::port_type port_num = 80;
    unsigned short port_num = 80;
    try {
        asio::ip::tcp::endpoint end_point(ip_address, port_num);
        asio::io_context ioc;
        asio::ip::tcp::socket socket(ioc, end_point.protocol());
        // socket 连接到端点
        socket.connect(end_point);
    } catch (boost::system::system_error &err) {
        std::cerr << "[error code]: " << err.code() << std::endl;
        std::cerr << "[error     ]: " << err.what() << std::endl;
        return 1;
    }
    return 0;
}

// 客户端连接的端点的地址为域名
int client_dns_connect_to_end_point() {
    std::string host {"blog.030215.xyz"};
    std::string port_num {"80"};
    asio::io_context ioc;
    asio::ip::tcp::resolver::query resolver_query(
        host,
        port_num,
        asio::ip::tcp::resolver::query::numeric_service
    );
    asio::ip::tcp::resolver resolver(ioc);
    try {
        // 域名解析的所有 IP
        asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query);
        asio::ip::tcp::socket socket(ioc);
        asio::connect(socket, it);
    } catch (boost::system::system_error &err) {
        std::cerr << "[error code]: " << err.code() << std::endl;
        std::cerr << "[error     ]: " << err.what() << std::endl;
        return 1;
    }
    return 0;
}

// 服务器接受连接
// 服务器监听
int server_accept_connection() {
    // 缓冲队列长度，实际大于指定长度
    const int backlog_size = 30;
    unsigned short port_num = 80;
    asio::ip::tcp::endpoint end_point(asio::ip::address_v4::any(), port_num);
    asio::io_context ioc;
    try {
        asio::ip::tcp::acceptor acceptor(ioc, end_point.protocol());
        // acceptor 绑定端点
        acceptor.bind(end_point);
        // acceptor 监听
        acceptor.listen(backlog_size);
        asio::ip::tcp::socket socket(ioc);
        // 将 socket 将给 acceptor 处理
        acceptor.accept(socket);
    } catch (boost::system::system_error &err) {
        std::cerr << "[error code]: " << err.code() << std::endl;
        std::cerr << "[error     ]: " << err.what() << std::endl;
        return 1;
    }
    return 0;
}

// 循环写
void write_to_socket(asio::ip::tcp::socket &socket) {
    std::string buf {"message"};
    std::size_t total_bytes_writen = 0; // 已写字节数
    while (total_bytes_writen != buf.length()) {
        total_bytes_writen += socket.write_some(
            asio::buffer(
                buf.c_str() + total_bytes_writen,
                buf.length() - total_bytes_writen
            )
        );
    }
}

void send_data_write_some() {
    std::string raw_ip_address = "192.168.1.1";
    unsigned short port_num = 3333;

    try {
        asio::ip::tcp::endpoint endpoint(
            asio::ip::address::from_string(raw_ip_address),
            port_num
        );
        asio::io_context ioc;
        asio::ip::tcp::socket socket(ioc, endpoint.protocol());
        socket.connect(endpoint);
        write_to_socket(socket);
    } catch (boost::system::system_error &err) {
        std::cerr << "[error code]: " << err.code() << std::endl;
        std::cerr << "[error     ]: " << err.what() << std::endl;
    }
}

// 一次写
int send_data_by_send() {
    std::string raw_ip_address {"192.168.1.1"};
    unsigned short port_num = 3333;
    std::string buf {"message"};
    try {
        asio::ip::tcp::endpoint endpoint(
            asio::ip::address::from_string(raw_ip_address),
            port_num
        );
        asio::io_context ioc;
        asio::ip::tcp::socket socket(ioc);
        socket.connect(endpoint);
        int send_len = socket.send(asio::buffer(
            buf.c_str(), buf.length()
        ));
        if (send_len < 0) {
            std::cerr << "system error" << std::endl;
        } else if (send_len == 0) {
            std::cerr << "endpoint shutdown" << std::endl;
        } else if (send_len == buf.length()) {
            std::cout << "send success" << std::endl;
        }
    } catch (boost::system::system_error &err) {
        std::cerr << "[error code]: " << err.code() << std::endl;
        std::cerr << "[error     ]: " << err.what() << std::endl;
    }
}

// 一次写
int send_data_by_write() {
    std::string buf {"hello"};
    std::string raw_ip_address {"127.0.0.1"};
    unsigned short port_num = 80;
    try {
        asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address);
        asio::ip::tcp::endpoint endpoint(ip_address, port_num);
        asio::io_context ioc;
        asio::ip::tcp::socket socket(ioc);
        socket.connect(endpoint);
        int send_len = asio::write(
            socket, asio::buffer(buf.c_str(), buf.length())
        );
        if (send_len < 0) {
            std::cerr << "system error" << std::endl;
        } else if (send_len == 0) {
            std::cerr << "endpoint shutdown" << std::endl;
        } else if (send_len == buf.length()) {
            std::cout << "send success" << std::endl;
        }
    } catch (boost::system::system_error &err) {
        std::cerr << "[error code]: " << err.code() << std::endl;
        std::cerr << "[error     ]: " << err.what() << std::endl;
    }
}

// tcp 循环读
std::string read_from_socket(asio::ip::tcp::socket &socket) {
    const unsigned char message_size = 7;
    char buf[message_size]; // 存放读取的数据
    std::size_t total_bytes_read = 0;
    while (total_bytes_read < message_size) {
        total_bytes_read += socket.read_some(
            asio::buffer(
                buf + total_bytes_read,
                message_size - total_bytes_read
            )
        );
    }
    return std::string(buf, total_bytes_read);
}

int read_data_by_read_some() {
    std::string buf {"hello"};
    std::string raw_ip_address {"127.0.0.1"};
    unsigned short port_num = 8080;
    try {
        asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address);
        asio::ip::tcp::endpoint endpoint(ip_address, port_num);
        asio::io_context io_context;
        asio::ip::tcp::socket socket(io_context);
        socket.connect(endpoint);
        read_from_socket(socket);
    } catch (boost::system::system_error &err) {
        std::cerr << "[error code]: " << err.code() << std::endl;
        std::cerr << "[error     ]: " << err.what() << std::endl;
    }
}

// 一次读
int read_data_by_receive() {
    try {
        asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string("127.0.0.1"), 8080);
        asio::io_context ioc;
        asio::ip::tcp::socket socket(ioc);
        socket.connect(endpoint);
        const unsigned char buff_size = 7;
        char buf[buff_size];
        int receive_len = socket.receive(
            asio::buffer(buf, buff_size)
        );
        if (receive_len < 0) {
            std::cerr << "error" << std::endl;
        } else if (receive_len == 0) {
            std::cerr << "endpoint shutdown" << std::endl;
        } else if (receive_len == buff_size) {
            std::cout << "success" << std::endl;
        }
    } catch (boost::system::system_error &err) {
        std::cerr << "[error code]: " << err.code() << std::endl;
        std::cerr << "[error     ]: " << err.what() << std::endl;
    }
}

// 一次读
int read_data_by_read() {
    try {
        asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string("127.0.0.1"), 80);
        asio::io_context ioc;
        asio::ip::tcp::socket socket(ioc);
        socket.connect(endpoint);
        const unsigned char buf_size = 7;
        char buf[buf_size];
        int receive_len = asio::read(socket, asio::buffer(buf, buf_size));
        if (receive_len < 0) {
            std::cerr << "system error" << std::endl;
        } else if (receive_len == 0) {
            std::cerr << "endpoint shutdown" << std::endl;
        } else if (receive_len == buf_size) {
            std::cout << "success" << std::endl;
        }
    } catch (boost::system::system_error &err) {
        std::cerr << "[error code]: " << err.code() << std::endl;
        std::cerr << "[error     ]: " << err.what() << std::endl;
    }
}