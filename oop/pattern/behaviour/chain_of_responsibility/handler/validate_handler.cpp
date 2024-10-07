#include "validate_handler.h"

void ValidateHandler::handleOrder(const Order &order) {
    if (order.getAmount() > 0) {
        std::cout << "order id #" << order.getId()
            << " validate successfully" << std::endl;
        if (next_handler_) {
            next_handler_->handleOrder(order);
        }
    } else {
        std::cout << "invalid order id # " << order.getId()
            << std::endl;
    }
}