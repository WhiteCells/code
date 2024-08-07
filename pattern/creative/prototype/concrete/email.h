#ifndef _EMAIL_H_
#define _EMAIL_H_

#include "prototype.h"
#include <string>
#include <iostream>

class Attachment {
public:
    Attachment() {}
    ~Attachment() {}

    void setContent(const std::string &content) {
        content_ = content;
    }

    std::string getContent() const {
        return content_;
    }

private:
    std::string content_;
};

class Email : public Prototype {
public:
    Email() {}
    Email(std::string text, std::string attachment_content)
        : text_(text), attachment_(new Attachment()) {
        attachment_->setContent(attachment_content);
    }
    ~Email() {
        if (attachment_) {
            delete attachment_;
            attachment_ = nullptr;
        }
    }

    Email *clone() override {
        return new Email(this->text_, this->attachment_->getContent());
    }

    void changeText(const std::string &text) {
        text_ = text;
    }

    void changeAttachment(const std::string &content) {
        attachment_->setContent(content);
    }

    void getEmailInfo() const {
        std::cout << text_ << std::endl;
        std::cout << attachment_->getContent() << std::endl;
    }

private:
    std::string text_;
    Attachment *attachment_;
};

#endif // _EMAIL_H_