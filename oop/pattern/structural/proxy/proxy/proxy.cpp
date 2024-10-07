#include "proxy.h"

CachedWebResource::CachedWebResource(AbstractWebResource *resource)
    : resource_(resource), page_info_cached_(), video_info_cached_(), request_(false) {

}

std::string CachedWebResource::getPageInfo() {
    if (page_info_cached_.empty() || request_) {
        page_info_cached_ = resource_->getPageInfo();
    }
    return page_info_cached_;
}

std::string CachedWebResource::getVideoInfo() {
    if (video_info_cached_.empty() || request_) {
        video_info_cached_ = resource_->getVideoInfo();
    }
    return video_info_cached_;
}