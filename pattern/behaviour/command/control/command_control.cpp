#include "command_control.h"

void CommandControl::setCommand(Command *command) {
    command_ = command;
}

void CommandControl::executeCommand() {
    if (command_) {
        command_->execute();
    } else {
        std::cout << "no command assigned" << std::endl;
    }
}