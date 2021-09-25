#include "ConfusionMatrixCommand.h"
#include "../Classifier.h"

ConfusionMatrixCommand::ConfusionMatrixCommand(DefaultIO* thisIO) {
    m_dio = thisIO;
    m_description = "display algorithm confusion matrix";
    m_thisClassifier = nullptr;
}
void ConfusionMatrixCommand::execute() {
    m_dio->write(m_thisClassifier->getConfusionMatrix());
    string emptyLine;
    do
    {
        emptyLine = m_dio->read();
    } while (!emptyLine.empty());
}