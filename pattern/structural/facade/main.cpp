#include "facade.h"

int main(int argc, char *argv[]) {
    Facade *facade = new Facade();
    facade->wrapSystemOperate();

    delete facade;
    return 0;
}