#include "turn_off_command.h"

TurnOffCommand::TurnOffCommand(std::string device)
    : device_(device) {

}

void TurnOffCommand::execute() {
    std::cout << "turn off " << device_ << std::endl;
}