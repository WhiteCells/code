#include "container.h"

int main(int argc, char *argv[]) {
    Container *sub = new Container();
    sub->add(0, new Dot(1, 1));
    sub->add(1, new Circle(1, 1, 1));

    Container *main = new Container();
    main->add(0, sub);
    main->move(1, 1);
    main->draw();

    delete main;
    return 0;
}