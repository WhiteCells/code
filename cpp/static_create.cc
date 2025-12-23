#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>

inline int64_t get_current_timestamp_seconds()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void createFile()
{
    // time
    int64_t timestamp = get_current_timestamp_seconds();
    std::string filename = std::to_string(timestamp) + ".txt";
    // create file
    std::filesystem::create_directories("bbb");
    std::cout << "current path: " << std::filesystem::current_path() << std::endl;
    std::ofstream file("bbb/" + filename);

    file << "Hello, World!" << std::endl;
    file.close();
}

int main(int argc, char *argv[])
{
    createFile();
    createFile();
    createFile();
    return 0;
}