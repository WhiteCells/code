#include "proxy.h"
#include "service.h"
#include <iostream>

int main(int argc, char *argv[]) {
    AbstractWebResource *web_resource = new WebResource("page1", "video1");
    CachedWebResource *proxy_web_resource = new CachedWebResource(web_resource);
    std::cout << proxy_web_resource->getPageInfo() << std::endl;
    std::cout << proxy_web_resource->getVideoInfo() << std::endl;

    AbstractWebResource *web_resource2 = new WebResource(proxy_web_resource);
    CachedWebResource *proxy_web_resource2 = new CachedWebResource(proxy_web_resource);
    std::cout << proxy_web_resource2->getPageInfo() << std::endl;
    std::cout << proxy_web_resource2->getVideoInfo() << std::endl;

    delete proxy_web_resource2;
    delete web_resource2;
    delete proxy_web_resource;
    delete web_resource;
    return 0;
}