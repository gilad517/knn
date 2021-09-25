#include "PrintingCommand.h"

PrintingCommand::PrintingCommand(DefaultIO* thisIO) {
    m_dio = thisIO;
    m_description = "display results";
    m_thisClassifier = nullptr;
}
void PrintingCommand::execute() {
    m_dio->write(m_thisClassifier->displayResults());
    string emptyLine;
    do
    {
        emptyLine = m_dio->read();
    } while (!emptyLine.empty());
}