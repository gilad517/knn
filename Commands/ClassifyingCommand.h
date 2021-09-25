#pragma once
#include <iostream>
#include "Command.h"
using namespace std;

class ClassifyingCommand : public Command{
    public:
        void execute();
        ClassifyingCommand(DefaultIO* thisIO);
};