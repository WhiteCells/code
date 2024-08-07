#ifndef _COMMAND_CONTROL_H_
#define _COMMAND_CONTROL_H_

#include "command.h"

class CommandControl {
public:
    void setCommand(Command *command);
    void executeCommand();
    
private:
    Command *command_;
};

#endif // _COMMAND_CONTROL_H_