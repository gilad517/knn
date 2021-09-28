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
        this_thread::sleep_for(chrono::milliseconds(100));
        m_dio->write("please enter a message");
        cout<<"  ."<<emptyLine<<".1"<<endl;
        emptyLine = m_dio->read();
        cout<<"  ."<<emptyLine<<".2"<<endl;
    } while (!emptyLine.empty());
}