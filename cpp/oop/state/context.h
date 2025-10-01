#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "state.h"
#include <memory>

class Context
{
public:
    void setState(std::shared_ptr<State> state)
    {
        m_state = state;
    }

    void handle()
    {
        if (m_state) {
            m_state->handle();
        }
    }

private:
    std::shared_ptr<State> m_state;
};

#endif // _CONTEXT_H_