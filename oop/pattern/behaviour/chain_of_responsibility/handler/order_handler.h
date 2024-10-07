#ifndef _ORDER_HANDLER_H_
#define _ORDER_HANDLER_H_

#include "order.h"
#include <iostream>

class OrderHandler {
public:
    virtual ~OrderHandler() = 0;
    virtual void handleOrder(const Order &order) = 0;
    void setNextHandler(OrderHandler *handler);

protected:
    OrderHandler *next_handler_;
};

#endif // _ORDER_HANDLER_H_