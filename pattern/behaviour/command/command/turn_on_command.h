#ifndef _TURN_ON_COMMAND_H_
#define _TURN_ON_COMMAND_H_

#include "command.h"

class TurnOnCommand : public Command {
public:
    TurnOnCommand(std::string device);
    virtual void execute() override;

private:
    std::string device_;
};

#endif // _TURN_ON_COMMAND_H_