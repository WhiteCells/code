#include "originator.h"
#include "caretaker.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Originator originator("111");
    Caretaker caretaker;
    caretaker.addMemento(originator.createMemento());
    originator.setState("222");
    std::cout << originator.getState() << std::endl;
    originator.restoreFromMemento(caretaker.getMemento(0));
    std::cout << originator.getState() << std::endl;
    return 0;
}