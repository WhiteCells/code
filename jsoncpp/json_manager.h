// #include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>
#include <string>

class JsonManager {
public:
    JsonManager(std::string json_path);


    bool parse();

private:
    std::string json_str;
    Json::Value receive_root_;
    Json::Reader reader_;
};