// #include "command.h"
#include "turn_off_command.h"
#include "turn_on_command.h"
#include "command_control.h"

int main(int argc, char *argv[]) {
    // create device
    Command *turn_on = new TurnOnCommand("device1");
    Command *turn_off = new TurnOffCommand("device2");

    // create control
    CommandControl *control = new CommandControl();
    control->setCommand(turn_on);
    control->executeCommand();
    control->setCommand(turn_off);
    control->executeCommand();

    delete control;
    control = nullptr;
    delete turn_off;
    turn_off = nullptr;
    delete turn_on;
    turn_on = nullptr;
    return 0;
}