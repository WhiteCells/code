#ifndef _PROCESS_HANDLER_H_
#define _PROCESS_HANDLER_H_

#include "order_handler.h"

class ProcessHandler : public OrderHandler {
public:
    virtual void handleOrder(const Order &order) override;
};

#endif // _PROCESS_HANDLER_H_