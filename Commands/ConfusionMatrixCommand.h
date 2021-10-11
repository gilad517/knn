#pragma once
#include <iostream>
#include "Command.h"
using namespace std;
/**
 * @brief The ConfusionMatrixCommand class represemts command 7 in the menu.
 * displaying the confusion matrix of the data classified.
 * extends the abstract class Command.
 */
class ConfusionMatrixCommand : public Command{
    public:
        //inherited method from the Command abstract class.
        void execute();
        
        /**
         * @brief Construct a new ConfusionMatrixCommand object given the DefaultIO to use for communication.
         * 
         * @param thisIO The DefaultIO to use for communication
         */
        ConfusionMatrixCommand(DefaultIO* thisIO);
};