#ifndef _PROXY_H_
#define _PROXY_H_

#include "service.h"

class CachedWebResource : public AbstractWebResource {
public:
    CachedWebResource(AbstractWebResource *resource);
    virtual std::string getPageInfo() override;
    virtual std::string getVideoInfo() override;

private:
    AbstractWebResource *resource_;
    std::string page_info_cached_;
    std::string video_info_cached_;
    bool request_;
};

#endif // _PROXY_H_