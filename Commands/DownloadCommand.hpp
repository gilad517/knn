#pragma once
#include <iostream>
#include "Command.hpp"
using namespace std;

class DownloadCommand : public Command{
    public:
        void execute();
        DownloadCommand(DefaultIO* thisIO);
};