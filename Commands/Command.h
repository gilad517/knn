#pragma once
#include <iostream>
#include "../DefaultIO.h"
#include "../Classifier.h"
#include <chrono>
#include <thread>
using namespace std;
/**
 * @brief The command abstract class is used to describe a command and its funcionality.
 * 
 */
class Command {
    public:
        /**
         * @brief A purely abstract method for executing the command
         * 
         */
        virtual void execute() = 0;

        /**
         * @brief Set the Classifier attribute of this command
         * 
         * @param newClassifier 
         */
        void setClassifier(Classifier* newClassifier) {
            m_thisClassifier = newClassifier;
        }

        /**
         * @brief Get the Description attribute of this command
         * 
         * @return string The Description attribute of this command
         */
        string getDescription() {
            return m_description;
        }
    protected:
        //The classifier used in the command
        Classifier* m_thisClassifier;
        //The command's description
        string m_description;
        //The DefaultIO used for all communications
        DefaultIO* m_dio;
};