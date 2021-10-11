#pragma once
#include <iostream>
#include "Command.h"
using namespace std;

/**
 * @brief The PrintingCommand class represemts command 4 in the menu.
 * displaying the classified results to the client.
 * extends the abstract class Command.
 */
class PrintingCommand : public Command{
    public:
        //inherited method from the Command abstract class.
        void execute();
        
        /**
         * @brief Construct a new PrintingCommand object given the DefaultIO to use for communication.
         * 
         * @param thisIO The DefaultIO to use for communication
         */
        PrintingCommand(DefaultIO* thisIO);
};