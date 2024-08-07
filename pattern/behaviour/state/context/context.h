#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "state.h"

class Context {
public:
    Context() {}

    Context(State *state) : state_(state) {}
    
    ~Context() {
        if (state_) {
            delete state_;
            state_ = nullptr;
        }
    }

    void setState(State *state) {
        if (state_) {
            delete state_;
            state_ = nullptr;
        }
        state_ = state;
    }

    void request() {
        if (state_) {
            state_->handle();
        }
    }

private:
    State *state_;
};

#endif // _CONTEXT_H_