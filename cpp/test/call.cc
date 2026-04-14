#include "call.h"
#include "acc.h"

Call::Call(Acc &acc) : m_acc(acc)
{
}

void Call::hangup()
{
    std::cout << __func__ << std::endl;
    m_acc.clear();
}