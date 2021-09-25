#include "ClassifyingCommand.h"

ClassifyingCommand::ClassifyingCommand(DefaultIO* thisIO) {
    m_dio = thisIO;
    m_description = "classify data";
    m_thisClassifier = nullptr;
}
void ClassifyingCommand::execute() {
    m_thisClassifier->setDataArray();
    m_dio->write("classifying data complete");
}