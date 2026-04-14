#pragma once
#include <memory>

class Call;

class Acc
{
public:
    void clear();

private:
    std::shared_ptr<Call> m_call;
};