#include "order.h"

Order::Order(int id, double amount)
    : id_(id), amount_(amount) {

}

int Order::getId() const {
    return id_;
}

double Order::getAmount() const {
    return amount_;
}