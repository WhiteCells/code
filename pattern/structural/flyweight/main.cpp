#include "pot_type_factory.h"
#include "normal_pot.h"
#include <vector>
#include <memory>
#include <chrono>
#include <iostream>

int main(int argc, char *argv[]) {
    /* pot type factory */
    PotTypeFactory *pot_type_factory = PotTypeFactory::getInstance();
    PotType *pot_type = pot_type_factory->getPot("a", "red", 10.0);

    std::vector<std::shared_ptr<Pot>> pot_v;

    auto start = std::chrono::high_resolution_clock::now();
    for (int x = 0; x < 1000; ++x) {
        for (int y = 0; y < 1000; ++y) {
            pot_v.push_back(std::make_shared<Pot>(x, y, pot_type));
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "factory pot type spend time: " << diff.count() << "s" << std::endl;

    // for (const auto &pot : pot_v) {
    //     pot->display();
    // }

    /* normal pot */
    std::vector<std::shared_ptr<NormalPot>> normal_pot_v;

    start = std::chrono::high_resolution_clock::now();
    for (int x = 0; x < 1000; ++x) {
        for (int y = 0; y < 1000; ++y) {
            normal_pot_v.push_back(std::make_shared<NormalPot>("b", "blue", 10.0, x, y));
        }
    }
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "normal pot spend time: " << diff.count() << "s" << std::endl;

    return 0;
}