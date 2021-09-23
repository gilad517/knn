#pragma once
#include "ClassifyingCommand.hpp"

class ClassifyingCommand : public Command{
    ClassifyingCommand(DefaultIO* thisIO) {
        m_dio = thisIO;
        m_description = "classify data";
        m_thisClassifier = nullptr;
    }
    void execute() {
        m_thisClassifier->setDataArray();
        m_dio->write("classifying data complete");
    }
};