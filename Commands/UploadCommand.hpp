#pragma once
#include <iostream>
#include "Command.hpp"
using namespace std;

class UploadCommand : public Command{
    public:
        void execute();
        UploadCommand(DefaultIO* thisIO);
};