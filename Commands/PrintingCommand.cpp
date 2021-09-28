#include "PrintingCommand.h"

PrintingCommand::PrintingCommand(DefaultIO* thisIO) {
    m_dio = thisIO;
    m_description = "display results";
    m_thisClassifier = nullptr;
}
void PrintingCommand::execute() {
    m_dio->write(m_thisClassifier->displayResults());
    this_thread::sleep_for(chrono::milliseconds(100));
    string emptyLine;
    do
    {
        m_dio->write("please enter a message");
        emptyLine = m_dio->read();
    } while (!emptyLine.empty());
}