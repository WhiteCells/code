#ifndef _LOGIC_SYSTEM_H_
#define _LOGIC_SYSTEM_H_

#include "node.h"
#include <memory>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <functional>
#include <thread>

/**
 * handle different types of message behavior
 */
class LogicSystem {
    using CallBack \
        = std::function<void(std::shared_ptr<LogicNode>, std::shared_ptr<Session>)>;

public:
    ~LogicSystem();
    static std::shared_ptr<LogicSystem> getInstance();

    void pushMessageToQueue(std::shared_ptr<LogicNode> node);

private:
    LogicSystem();
    LogicSystem(const LogicSystem &) = delete;
    LogicSystem &operator=(const LogicSystem &) = delete;

    void handleMessageThreadFunc();
    void registerCallBack();

    void echoMessageCallBack(
        std::shared_ptr<LogicNode> node,
        std::shared_ptr<Session> session
    );

    class Deletor {
        void operator()(LogicSystem *);
    };

    static std::shared_ptr<LogicSystem> instance_;

    std::thread handle_message_thread_;
    std::mutex mutex_;
    std::atomic_bool has_stop_;
    std::condition_variable consumer_;
    std::queue<std::shared_ptr<LogicNode>> nodes_que_;
    std::unordered_map<NODE_ID_TYPE, CallBack> callbacks_;
};

#endif // _LOGIC_SYSTEM_H_