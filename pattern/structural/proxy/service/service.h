#ifndef _SERVICE_H_
#define _SERVICE_H_

#include <iostream>

class AbstractWebResource {
public:
    virtual std::string getPageInfo() = 0;
    virtual std::string getVideoInfo() = 0;
};

class WebResource : public AbstractWebResource {
public:
    WebResource(AbstractWebResource *resource);
    WebResource(std::string page_info, std::string video_info);
    virtual std::string getPageInfo() override;
    virtual std::string getVideoInfo() override;

private:
    std::string page_info_;
    std::string video_info_;
};

#endif // _SERVICE_H_