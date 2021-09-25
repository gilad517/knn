#pragma once
#include <iostream>
#include "Command.h"
using namespace std;

class ConfusionMatrixCommand : public Command{
    public:
        void execute();
        ConfusionMatrixCommand(DefaultIO* thisIO);
};