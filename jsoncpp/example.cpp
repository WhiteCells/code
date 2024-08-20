// #include <json/json.h>
#include <json/reader.h>
#include <json/value.h>
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
    // std::string json_str = "{\"host\": \"127.0.0.1\",\"port\": \"4403\",\"pool\": {\"size\": 10,\"timeout\": 1000},\"auth\": \"1&d2*D)_3$\",\"secure\": true}";
    std::ifstream json_file("server.json");
    if (!json_file.is_open()) {
        std::cerr << "json open failed" << std::endl;
        return EXIT_FAILURE;
    }
    Json::Value root1;
    json_file >> root1;

    std::string root1_str = root1.toStyledString();
    std::cout << root1_str << std::endl;

    Json::Reader reader;
    Json::Value root1_res;
    // convert json to Json::Value
    reader.parse(root1_str, root1_res);
    std::cout << root1_res["pool"]["size"].toStyledString() << std::endl;
    std::cout << root1_res["auth"].toStyledString() << std::endl;

    Json::Value root2;
    root2["name"] = "name1";
    root2["pass"] = "pass";
    Json::Value root2_sub1;
    root2_sub1["contact"] = "145321";
    root2_sub1["address"] = "xx1-xx2";
    root2_sub1["info"] = root2_sub1;
    std::string root2_str = root2.toStyledString();
    std::cout << root2_str << std::endl;
    return 0;
}