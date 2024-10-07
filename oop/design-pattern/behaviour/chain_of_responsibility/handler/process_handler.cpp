#include "process_handler.h"

void ProcessHandler::handleOrder(const Order &order) {
    if (order.getAmount() > 0) {
        std::cout << "order id #" << order.getId()
            << " process successfully" << std::endl;
        if (next_handler_) {
            next_handler_->handleOrder(order);
        }
    } else {
        std::cout << "invalid order #"
            << order.getId() << std::endl;
    }
}