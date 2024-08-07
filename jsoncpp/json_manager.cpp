#include "json_manager.h"
#include <iostream>
#include <fstream>

JsonManager::JsonManager(std::string json_path) {
    std::ifstream json_file(json_path);
    if (!json_file.is_open()) {
        std::cerr << "json path error" << std::endl;
        return;
    }
    json_file >> receive_root_;
    std::cout << receive_root_ << std::endl;
}

bool JsonManager::parse() {
    std::cout << receive_root_["pool"]["size"] << std::endl;
    return true;
}