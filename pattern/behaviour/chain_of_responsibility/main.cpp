#include "order.h"
#include "process_handler.h"
#include "validate_handler.h"
#include "ship_handler.h"

int main(int argc, char *argv[]) {
    // create handler
    OrderHandler *validate_handler = new ValidateHandler();
    OrderHandler *process_handler = new ProcessHandler();
    OrderHandler *ship_handler = new ShipHandler();

    // set up chain of responsibility
    validate_handler->setNextHandler(process_handler);
    process_handler->setNextHandler(ship_handler);
    
    // process orders using chain of responsibility
    validate_handler->handleOrder(Order(1, 0.1));
    validate_handler->handleOrder(Order(2, 0.3));
    validate_handler->handleOrder(Order(3, 0.0));

    delete ship_handler;
    ship_handler = nullptr;
    delete process_handler;
    process_handler = nullptr;
    delete validate_handler;
    validate_handler = nullptr;
    return 0;
}