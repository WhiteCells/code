#include "real_estate_mediator.h"

RealEstateMediator::~RealEstateMediator() {
    for (auto &user : user_list_) {
        if (user) {
            delete user;
            user = nullptr;
        }
    }
}

void RealEstateMediator::registerUser(User *user) {
    user_list_.push_back(user);
}

void RealEstateMediator::operate(User *ask_user) {
    USER_TYPE ask_user_type = ask_user->getUserType();
    std::cout << (ask_user_type == USER_TYPE::TENANT ? "afford: " : "profitable: ") << std::endl;
    for (const auto &user : user_list_) {
        bool is_diff_user_type = user->getUserType() ^ ask_user->getUserType();
        bool is_afford = ask_user_type == USER_TYPE::TENANT ? \
            ask_user->getPrice() >= user->getPrice() \
            : ask_user->getPrice() <= user->getPrice();
        if (is_diff_user_type && is_afford) {
            user->answer();
        }
    }
    std::cout << "---" << std::endl;
}