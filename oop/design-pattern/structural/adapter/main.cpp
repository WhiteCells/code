#include "hole.h"
#include "square.h"
#include "round_adapter.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Square *square = new Square(10);
    Hole *hole = new Hole(5);

    // hole->isAccommodate(square); // compilation failed

    RoundAdapter *round_adapter = new RoundAdapter(square);
    std::cout << (hole->isAccommodate(round_adapter) ? \
                  "accommodate" : "not accommodate") << std::endl;

    delete square;
    delete hole;
    delete round_adapter;
    return 0;
}