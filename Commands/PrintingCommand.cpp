#pragma once
#include "PrintingCommand.hpp"

class PrintingCommand : public Command{
    PrintingCommand(DefaultIO* thisIO) {
        m_dio = thisIO;
        m_description = "display results";
        m_thisClassifier = nullptr;
    }
    void execute() {
        m_dio->write(m_thisClassifier->displayResults());
        m_dio->write("Done.");
        string emptyLine;
        do
        {
            emptyLine = m_dio->read();
        } while (emptyLine.compare("")!=0);
    }
};