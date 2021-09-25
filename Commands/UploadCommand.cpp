#include "UploadCommand.h"

UploadCommand::UploadCommand(DefaultIO* thisIO) {
    m_dio = thisIO;
    m_description = "upload an unclassified csv data file";
    m_thisClassifier = nullptr;
}
void UploadCommand::execute() {
    m_dio->write("Please upload your local train CSV file.");
    string trainPath(m_dio->read());
    m_thisClassifier->initialize(trainPath);
    m_dio->write("Upload complete.");
    m_dio->write("Please upload your local test CSV file.");
    string testPath(m_dio->read());
    m_thisClassifier->addTest(testPath);
    m_dio->write("Upload complete.");
}