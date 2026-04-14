#include "acc.h"
#include "call.h"

void Acc::clear()
{
    // if (m_call) {
    m_call.reset();
    std::cout << "reset m_call" << std::endl;
    // }
}
