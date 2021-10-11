#pragma once
#include <iostream>
#include "Command.h"
using namespace std;
/**
 * @brief The ClassifyingCommand class represemts command 3 in the menu.
 * classifying the existant data objects in the classifier.
 * extends the abstract class Command.
 */
class ClassifyingCommand : public Command{
    public:
        //inherited method from the Command abstract class.
        void execute();

        /**
         * @brief Construct a new ClassifyingCommand object given the DefaultIO to use for communication.
         * 
         * @param thisIO The DefaultIO to use for communication
         */
        ClassifyingCommand(DefaultIO* thisIO);
};