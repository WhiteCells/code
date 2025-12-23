#include <regex>
#include <fstream>
#include <filesystem>
#include <iostream>

static bool match_by_rules(const std::string &str, const std::filesystem::path &rules_file)
{
    std::ifstream ifs(rules_file);
    if (!ifs.is_open()) {
        return false;
    }

    std::string pattern;
    while (std::getline(ifs, pattern)) {
        if (pattern.empty()) {
            continue;
        }

        try {
            std::regex reg(pattern);
            if (std::regex_search(str, reg)) {
                return true;
            }
        }
        catch (...) {
            continue;
        }
    }

    return false;
}

static bool regex_match_from_root(const std::string &str,
                                  const std::filesystem::path &root_path = "./")
{
    if (!std::filesystem::exists(root_path) || !std::filesystem::is_directory(root_path)) {
        return false;
    }

    for (const auto &entry : std::filesystem::directory_iterator(root_path)) {
        const auto &path = entry.path();
        if (path.extension() != ".regex") {
            continue;
        }
        if (match_by_rules(str, path)) {
            std::cout << "match: " << path.string() << std::endl;
            return true;
        }
    }
    return false;
}

int main()
{
    std::string str = "，我知道呀";
    if (regex_match_from_root(str)) {
        std::cout << "match" << std::endl;
    }
    else {
        std::cout << "not match" << std::endl;
    }
    return 0;
}