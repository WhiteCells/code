#include "tenant.h"

Tenant::Tenant(std::string name, std::string address,
               std::string phone, double price, Mediator *mediator)
    : User(name, address, phone, price, USER_TYPE::TENANT, mediator) {

}

Tenant::~Tenant() {
    std::cout << "tenant destruct" << std::endl;
}

void Tenant::ask() {
    std::cout << "tenant: " << name_ << " ask: " << price_ << std::endl;
    this->getMediator()->operate(this);
}

void Tenant::answer() {
    std::cout << "tenant: " << name_ << " answer: " << price_ << std::endl;
}