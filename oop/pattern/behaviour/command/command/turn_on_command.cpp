#include "turn_on_command.h"

TurnOnCommand::TurnOnCommand(std::string device)
    : device_(device) {

}

void TurnOnCommand::execute() {
    std::cout << "turn on " << device_ << std::endl;
}