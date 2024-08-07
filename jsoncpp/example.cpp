#include "json_manager.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    // std::string json_str = "{\"host\": \"127.0.0.1\",\"port\": \"4403\",\"pool\": {\"size\": 10,\"timeout\": 1000},\"auth\": \"1&d2*D)_3$\",\"secure\": true}";
    JsonManager json_manager("server.json");
    json_manager.parse();
    return 0;
}