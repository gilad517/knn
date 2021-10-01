#pragma once
#include <iostream>
#include "Command.h"
using namespace std;

class DownloadCommand : public Command{
    public:
        void execute();
        void execute(string downloadPath);
        DownloadCommand(DefaultIO* thisIO);
        static void activate(DownloadCommand* ptr, int& curr_threads, string downloadPath);
};