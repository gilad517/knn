#pragma once
#include <iostream>
#include "Command.hpp"
using namespace std;

class SettingsCommand : public Command {
    public:
        void execute();
        SettingsCommand(DefaultIO* thisIO);
};