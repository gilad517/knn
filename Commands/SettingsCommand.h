#pragma once
#include <iostream>
#include "Command.h"
using namespace std;

/**
 * @brief The SettingsCommand class represemts command 2 in the menu.
 * displaying and changing the classifier's settings.
 * extends the abstract class Command.
 */
class SettingsCommand : public Command {
    public:
        //inherited method from the Command abstract class.
        void execute();
        
        /**
         * @brief Construct a new SettingsCommand object given the DefaultIO to use for communication.
         * 
         * @param thisIO The DefaultIO to use for communication
         */
        SettingsCommand(DefaultIO* thisIO);
};