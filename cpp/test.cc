// #include <chrono>
// #include <iostream>
// #include <vector>

// inline int64_t get_current_timestamp_seconds()
// {
//     return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
// }

// inline int64_t get_current_timestamp_milliseconds()
// {
//     return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
// }

// inline bool find(std::string text)
// {
//     if (text.rfind("ENDENDEND", 0) == 0) {
//         std::cout << "llm required hangup" << std::endl;
//         return true;
//     }
//     return false;
// }

// #include <iostream>
// #include <thread>
// #include <chrono>
// #include <functional>

// void run_after(std::chrono::milliseconds delay, std::function<void()> task)
// {
//     // 启动一个独立线程
//     std::thread([delay, task]() {
//         std::this_thread::sleep_for(delay); // 等待
//         task();                             // 执行任务
//     }).detach();                            // 分离线程，自动回收
// }

// int main(int argc, char *argv[])
// {
//     std::cout << get_current_timestamp_seconds() << std::endl;
//     std::cout << get_current_timestamp_milliseconds() << std::endl;
//     std::cout << find("ENDENDEND12391823") << std::endl;
//     std::vector<char> flag1 = {'E', 'N', 'D'};
//     std::vector<char> flag2 = {'E', 'N', 'D'};
//     if (flag1 == flag2) {
//         std::cout << "flag1 == flag2" << std::endl;
//     }
//     else {
//         std::cout << "flag1 != flag2" << std::endl;
//     }

//     int a = 2;
//     char a_c = static_cast<char>('0' + a);
//     std::cout << a_c << std::endl;

//     float total_play_cast = 1.1;
//     char sleep_time = static_cast<char>('0' + (int)total_play_cast);

//     unsigned char sleep_time2 = static_cast<unsigned char>('1');
//     std::cout << sleep_time2 << std::endl;

//     run_after(std::chrono::seconds(5), []() {
//         std::cout << "111" << std::endl;
//     });

//     // while (1) {
//     // }
//     return 0;
// }

#include <unordered_map>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    std::unordered_map<int, std::string> m;
    // std::cout << m[1] << std::endl;
    std::cout << m[1] << std::endl;
    std::cout << m.find(1)->first << std::endl;
    // std::cout << m.find(2)->first << std::endl;
    // std::cout << m.find(2)->first << std::endl;
    auto it = m.find(1);
    if (it != m.end()) {
        std::cout << "find 1: " << it->second << std::endl;
    }
    return 0;
}