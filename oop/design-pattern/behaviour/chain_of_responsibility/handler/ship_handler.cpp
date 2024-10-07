#include "ship_handler.h"

void ShipHandler::handleOrder(const Order &order) {
    if (order.getAmount() > 0) {
        std::cout << "order id #" << order.getId()
            << " ship successfully" << std::endl;
        // no next handler
        // if (next_handler_) {
        //     next_handler_->handleOrder(order);
        // }
    } else {
        std::cout << "Invalid order id # "
            << order.getId() << std::endl;
    }
}