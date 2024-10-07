#ifndef _STRATEGY_H_
#define _STRATEGY_H_

class Strategy {
public:
    virtual ~Strategy() = 0;
    virtual void execute() = 0;
};

#endif // _STRATEGY_H_