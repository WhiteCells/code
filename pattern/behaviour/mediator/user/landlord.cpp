#include "landlord.h"

Landlord::Landlord(std::string name, std::string address,
                   std::string phone, double price, Mediator *mediator)
    : User(name, address, phone, price, USER_TYPE::LANDLORD, mediator) {

}

Landlord::~Landlord() {
    std::cout << "landlord destruct" << std::endl;
}

void Landlord::ask() {
    std::cout << "landlord: " << name_ << " ask: " << price_ << std::endl;
    this->getMediator()->operate(this);
}

void Landlord::answer() {
    std::cout << "landlord: " << name_ << " answer: " << price_ << std::endl;
}