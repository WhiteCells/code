#include "user.h"

User::User(std::string name, std::string address,
           std::string phone, double price,
           USER_TYPE type, Mediator *mediator)
    : name_(name), address_(address), phone_(phone_),
    price_(price), type_(type), mediator_(mediator) {

}

User::~User() {
    std::cout << "user destruct" << std::endl;
}

void User::setMediator(Mediator *mediator) {
    mediator_ = mediator;
}

Mediator *User::getMediator() const {
    return mediator_;
}

void User::setPersonType(USER_TYPE type) {
    type_ = type;
}

USER_TYPE User::getUserType() const {
    return type_;
}

double User::getPrice() const {
    return price_;
}