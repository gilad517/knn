#pragma once
#include <iostream>
#include "Command.h"
using namespace std;

/**
 * @brief The DownloadCommand class represemts command 5 in the menu.
 * downloading the classified results to a known location.
 * extends the abstract class Command.
 */
class DownloadCommand : public Command{
    public:
        //inherited method from the Command abstract class.
        void execute();

        /**
         * @brief Executing the DownloadCommand with a given location to download to.
         * 
         * @param downloadPath A given location to download to
         */
        void execute(string downloadPath);

        /**
         * @brief Construct a new DownloadCommand object given the DefaultIO to use for communication.
         * 
         * @param thisIO The DefaultIO to use for communication
         */
        DownloadCommand(DefaultIO* thisIO);

        /**
         * @brief A wrapper for the execution of the DownloadCommand.
         * given to a thread and executes the command.
         * @param ptr A pointer to the DownloadCommand we want to execute.
         * @param curr_threads The number of threads currently working
         * @param downloadPath A given location to download to
         */
        static void activate(DownloadCommand* ptr, int& curr_threads, string downloadPath);
};