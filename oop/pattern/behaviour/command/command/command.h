#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>
#include <iostream>

class Command {
public:
    virtual ~Command() = 0;
    virtual void execute() = 0;
};

#endif // _COMMAND_H_