#ifndef _TURN_OFF_COMMAND_H_
#define _TURN_OFF_COMMAND_H_

#include "command.h"

class TurnOffCommand : public Command {
public:
    TurnOffCommand(std::string device);
    virtual void execute() override;

private:
    std::string device_;
};

#endif // _TURN_OFF_COMMAND_H_