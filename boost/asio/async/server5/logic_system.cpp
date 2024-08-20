#include "logic_system.h"
#include "session.h"
#include <iostream>

std::shared_ptr<LogicSystem> LogicSystem::instance_ = nullptr;

std::shared_ptr<LogicSystem> LogicSystem::getInstance() {
    static std::once_flag flag;
    std::call_once(flag, []() {
        // instance_ = std::make_shared<LogicSystem>();
        instance_ = std::shared_ptr<LogicSystem>(new LogicSystem());
        // instance_ = std::make_shared<LogicSystem>([](LogicSystem *logic_system) {
        //     delete logic_system;
        // });
    });
    return instance_;
}

void LogicSystem::pushMessageToQueue(std::shared_ptr<LogicNode> node) {
    std::lock_guard<std::mutex> lock(mutex_);
    nodes_que_.push(node);
    consumer_.notify_one();
}

LogicSystem::LogicSystem() {
    std::cout << "LogicSystem()" << std::endl;
    registerCallBack();
    handle_message_thread_ = std::thread(
        &LogicSystem::handleMessageThreadFunc, this
    );
}

LogicSystem::~LogicSystem() {
    std::cout << "~LogicSystem()" << std::endl;
    has_stop_ = true;
    handle_message_thread_.join();
    consumer_.notify_one();
}

void LogicSystem::handleMessageThreadFunc() {
    for (;;) {
        std::unique_lock<std::mutex> ulock(mutex_);
        consumer_.wait(ulock, [this]() {
            return !nodes_que_.empty() || has_stop_;
        });
        if (has_stop_) {
            while (!nodes_que_.empty()) {
                auto node = nodes_que_.front();
                nodes_que_.pop();
                auto callback_iter = callbacks_.find(node->getId());
                if (callback_iter == callbacks_.end()) {
                    continue;
                }
                callback_iter->second(node, node->getSession());
            }
            break;
        }
        auto node = nodes_que_.front();
        nodes_que_.pop();
        auto callback_iter = callbacks_.find(node->getId());
        if (callback_iter == callbacks_.end()) {
            continue;
        }
        callback_iter->second(node, node->getSession());
    }
}

void LogicSystem::registerCallBack() {
    callbacks_[10101] = std::bind(
        &LogicSystem::echoMessageCallBack,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    );
}

void LogicSystem::echoMessageCallBack(
    std::shared_ptr<LogicNode> node,
    std::shared_ptr<Session> session
) {
    short id = node->getId();
    short len = node->getRecvNodeMessage()->len_;
    const char *message = node->getRecvNodeMessage()->getMessage();
    session->send(id, len, message);
}

void LogicSystem::Deletor::operator()(LogicSystem *logic_system) {
    delete logic_system;
}

