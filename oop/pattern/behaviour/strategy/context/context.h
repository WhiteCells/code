#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "strategy.h"

class Context {
public:
    Context(Strategy *strategy);
    ~Context();
    void setStrategy(Strategy *strategy);
    void process();

private:
    Strategy *strategy_;
};

#endif // _CONTEXT_H_