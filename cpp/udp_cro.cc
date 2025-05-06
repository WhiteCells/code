#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <chrono>
#include <arpa/inet.h>
#include <unistd.h>

void udp_sender(const std::string& ip, int port, const std::string& message, int count, int thread_id) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        return;
    }

    sockaddr_in target{};
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &target.sin_addr);

    for (int i = 0; i < count; ++i) {
        std::string msg = "[Thread " + std::to_string(thread_id) + "] " + message + " #" + std::to_string(i);
        sendto(sockfd, msg.c_str(), msg.size(), 0, (sockaddr*)&target, sizeof(target));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // 控制发包速率
    }

    close(sockfd);
}

int main() {
    std::string target_ip = "8.139.48.29";
    int target_port = 8888;
    int thread_count = 16;
    uint packets_per_thread = 1000;
    std::string payload = "Hello UDP";

    std::vector<std::thread> threads;

    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back(udp_sender, target_ip, target_port, payload, packets_per_thread, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "UDP sending completed." << std::endl;
    return 0;
}
