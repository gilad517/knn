#pragma once
#include <iostream>
#include "Command.h"
using namespace std;

class SettingsCommand : public Command {
    public:
        void execute();
        SettingsCommand(DefaultIO* thisIO);
};