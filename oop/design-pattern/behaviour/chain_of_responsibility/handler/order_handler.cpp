#include "order_handler.h"

OrderHandler::~OrderHandler() {

}

void OrderHandler::setNextHandler(OrderHandler *order) {
    next_handler_ = order;
}