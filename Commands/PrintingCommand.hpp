#pragma once
#include <iostream>
#include "Command.hpp"
using namespace std;

class PrintingCommand : public Command{
    public:
        void execute();
        PrintingCommand(DefaultIO* thisIO);
};