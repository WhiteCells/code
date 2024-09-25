#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

class HttpConnection :
    public std::enable_shared_from_this<HttpConnection>
{
public:
    HttpConnection(asio::ip::tcp::socket socket) :
        socket_(std::move(socket))
    {
        // read index.html
        std::ifstream file("./index.html");
        if (!file.is_open()) {
            std::cerr << "index.html not found" << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            html_index_ += line + '\n';
        }
        std::cout << html_index_;
        file.close();

        file.open("./404.html");
        if (!file.is_open()) {
            std::cerr << "404.html not found" << std::endl;
            return;
        }
        while (std::getline(file, line)) {
            html_404_ += line + '\n';
        }
        std::cout << html_404_;

        file.close();
    }

    void start()
    {
        // 读请求
        readRequst();
        // 超时检测
        checkDeadline();
    }

private:
    void readRequst()
    {
        auto self = shared_from_this();
        http::async_read(socket_, buffer_, request_, [self](boost::system::error_code err_code, std::size_t bytes_transferred) {
            boost::ignore_unused(bytes_transferred);
            if (err_code) {
                std::cout << "read request error: " << err_code.message() << std::endl;
                return;
            }
            self->processRequest();
        });
    }

    // 处理请求
    void processRequest()
    {
        response_.version(request_.version());
        response_.keep_alive(false);
        switch (request_.method()) {
            case http::verb::get:
                response_.result(http::status::ok);
                response_.set(http::field::server, "http-server1");
                createGetResponse();
                break;
            case http::verb::post:
                response_.result(http::status::ok);
                response_.set(http::field::server, "http-server1");
                createPostResponse();
                break;
            default:
                response_.result(http::status::bad_request);
                response_.set(http::field::content_type, "text/plain");
                beast::ostream(response_.body()) << "invalide request-method " << std::string(request_.method_string());
                break;
        }
        writeResponse();
    }

    // 创建 GET 回包
    void createGetResponse()
    {
        // 路由
        if (request_.target() == "/index") {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body()) << html_index_;
        }
        else if (request_.target() == "/visitor-count") {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body()) << html_index_;
        }
        else if (request_.target() == "/time") {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body()) << html_index_;
        }
        else {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body()) << html_404_;
        }
    }

    // 创建 POST 回包
    void createPostResponse()
    {
        if (request_.target() == "/register") {
            auto &body = this->request_.body();
            auto body_str = beast::buffers_to_string(body.data());
            std::cout << "recv body: " << body_str << std::endl;
        }
    }

    // 发送回包
    void writeResponse()
    {
        auto self = shared_from_this();
        response_.content_length(response_.body().size());
        http::async_write(socket_, response_, [self](boost::system::error_code err_code, std::size_t bytes_transffered) {
            if (err_code) {
                std::cerr << "write response error: " << err_code.message();
                return;
            }
            // 发送完成后，服务器关闭该连接，关闭服务器发送端
            self->socket_.shutdown(asio::ip::tcp::socket::shutdown_send);
            self->deadline_.cancel();
        });
    }

    // 判断定时器是否超时
    void checkDeadline()
    {
        auto self = shared_from_this();
        // 捕获 self 以增加对象的引用计数
        // 防止 HttpConnection 对象被销毁后出现访问无效内存的风险
        deadline_.async_wait([self](boost::system::error_code err_code) {
            if (err_code) {
                std::cout << "check dead line error: " << err_code.message() << std::endl;
                return;
            }
            self->socket_.close();
        });
    }

    asio::ip::tcp::socket socket_;
    beast::flat_buffer buffer_ {8192}; // 8k
    http::request<http::dynamic_body> request_;
    http::response<http::dynamic_body> response_;
    asio::steady_timer deadline_ {
        socket_.get_executor(), std::chrono::seconds(60)};

    std::string html_index_;
    std::string html_404_;
};

// void acceptHttpServerConnection(asio::ip::tcp::acceptor &acceptor)
// {
//     // asio::io_context ioc;
//     // asio::ip::tcp::socket socket(ioc); // error
//     asio::io_context ioc;
//     auto socket = std::make_shared<asio::ip::tcp::socket>(ioc); // error
//     acceptor.async_accept(*socket, [&](boost::system::error_code err_code) {
//         if (err_code) {
//             std::cerr << "accept error: " << err_code.message() << std::endl;
//         }
//         std::make_shared<HttpConnection>(std::move(*socket))->start();
//         acceptHttpServerConnection(acceptor);
//     });
// }

void acceptHttpServerConnection(asio::ip::tcp::acceptor &acceptor)
{
    // Accept new connection on a fresh socket
    acceptor.async_accept([&acceptor](boost::system::error_code err_code, asio::ip::tcp::socket socket) {
        if (err_code) {
            std::cerr << "accept error: " << err_code.message() << std::endl;
        }
        else {
            // HttpConnection hc(std::move(socket));
            // hc.start(); // error
            std::make_shared<HttpConnection>(std::move(socket))->start();
        }
        // Continue accepting more connections
        acceptHttpServerConnection(acceptor);
    });
}

class Server
{
public:
    Server(asio::io_context &ioc, uint port) :
        ioc_(ioc), prot_(port), socket_(ioc), acceptor_(ioc, {asio::ip::tcp::v4(), 8080})
    {
    }

    void start()
    {
        acceptor_.async_accept(socket_, [&](boost::system::error_code err_code) {
            if (err_code) {
                std::cerr << "accept error: " << err_code.message() << std::endl;
            }
            std::make_shared<HttpConnection>(std::move(socket_))->start();
            start();
        });
    }

private:
    asio::io_context &ioc_;
    uint prot_;
    asio::ip::tcp::socket socket_;
    asio::ip::tcp::acceptor acceptor_;
};

int main(int argc, char *argv[])
{
    // error
    // HttpConnection hc(std::move(socket_));
    // hc.start();

    try {
        asio::io_context ioc;
        asio::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait([&ioc](boost::system::error_code err_code, int signal_num) {
            if (err_code) {
                std::cout << "caught signal error: " << err_code.message() << std::endl;
                return;
            }
            std::cout << "caught signal: " << signal_num << std::endl;
            ioc.stop();
        });
        // asio::ip::tcp::acceptor acceptor(ioc, {asio::ip::tcp::v4(), 8080});
        // acceptHttpServerConnection(acceptor);
        Server server(ioc, 8080);
        server.start();
        ioc.run();
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}