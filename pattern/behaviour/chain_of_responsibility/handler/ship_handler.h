#ifndef _SHIP_HANDLER_H_
#define _SHIP_HANDLER_H_

#include "order_handler.h"

class ShipHandler : public OrderHandler {
public:
    virtual void handleOrder(const Order &order) override;
};

#endif // _SHIP_HANDLER_H_