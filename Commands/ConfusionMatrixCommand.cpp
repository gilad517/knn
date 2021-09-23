#pragma once
#include "ConfusionMatrixCommand.hpp"

class ConfusionMatrixCommand : public Command{
    ConfusionMatrixCommand(DefaultIO* thisIO) {
        m_dio = thisIO;
        m_description = "display algorithm confusion matrix";
        m_thisClassifier = nullptr;
    }
    void execute() {
        m_dio->write(m_thisClassifier->getConfusionMatrix());
        string emptyLine;
        do
        {
            emptyLine = m_dio->read();
        } while (emptyLine.compare("")!=0);
    }
};