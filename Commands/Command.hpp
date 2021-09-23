#pragma once
#include <iostream>
#include "../DefaultIO.hpp"
#include "../Classifier.h"
using namespace std;

class Command {
    public:
        virtual void execute() = 0;
        void setClassifier(Classifier* newClassifier) {
            m_thisClassifier = newClassifier;
        }
        string getDescription() {
            return m_description;
        }
    protected:
        Classifier* m_thisClassifier;
        string m_description;
        DefaultIO* m_dio;
};