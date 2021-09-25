#pragma once
#include <iostream>
#include "Command.h"
using namespace std;

class UploadCommand : public Command{
    public:
        void execute();
        UploadCommand(DefaultIO* thisIO);
};