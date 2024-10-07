#ifndef _VALIDATE_HANDLER_H_
#define _VALIDATE_HANDLER_H_

#include "order_handler.h"

class ValidateHandler : public OrderHandler {
public:
    virtual void handleOrder(const Order &order) override;
};

#endif // _VALIDATE_HANDLER_H_