#include "UploadCommand.h"

UploadCommand::UploadCommand(DefaultIO* thisIO) {
    m_dio = thisIO;
    m_description = "upload an unclassified csv data file";
    m_thisClassifier = nullptr;
}
void UploadCommand::execute() {
    m_dio->write("Please upload your local train CSV file.");
    this_thread::sleep_for(chrono::milliseconds(100));
    m_dio->write("please enter a message");
    string trainPath(m_dio->read());
    m_thisClassifier->initialize(trainPath);
    m_dio->write("Upload complete.");
    this_thread::sleep_for(chrono::milliseconds(100));
    m_dio->write("Please upload your local test CSV file.");
    this_thread::sleep_for(chrono::milliseconds(100));
    m_dio->write("please enter a message");
    string testPath(m_dio->read());
    m_thisClassifier->addTest(testPath);
    m_dio->write("Upload complete.");
}