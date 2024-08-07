#ifndef _HTTP_CONNECT_H_
#define _HTTP_CONNECT_H_

// class Addr;

namespace net {

class Addr;

class HttpConnect {
public:
    HttpConnect(const net::Addr &);
};

} // namespace net

#endif // _HTTP_CONNECT_H_