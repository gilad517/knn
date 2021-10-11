#pragma once
#include <iostream>
#include "Command.h"
using namespace std;

/**
 * @brief The UploadCommand class represemts command 1 in the menu.
 * uploading the train and test files to the classifier.
 * extends the abstract class Command.
 */
class UploadCommand : public Command{
    public:
        //inherited method from the Command abstract class.
        void execute();
        
        /**
         * @brief Construct a new UploadCommand object given the DefaultIO to use for communication.
         * 
         * @param thisIO The DefaultIO to use for communication
         */
        UploadCommand(DefaultIO* thisIO);
};