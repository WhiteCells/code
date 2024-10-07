#include "service.h"

WebResource::WebResource(AbstractWebResource *resource)
    : page_info_(resource->getPageInfo()),
    video_info_(resource->getVideoInfo()) {

}

WebResource::WebResource(std::string page_info, std::string video_info)
    : page_info_(page_info), video_info_(video_info) {

}

std::string WebResource::getPageInfo() {
    return page_info_;
}

std::string WebResource::getVideoInfo() {
    return video_info_;
}