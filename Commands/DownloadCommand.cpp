#include "DownloadCommand.h"

DownloadCommand::DownloadCommand(DefaultIO* thisIO) {
    m_dio = thisIO;
    m_description = "download results";
    m_thisClassifier = nullptr;
}
void DownloadCommand::execute() {
    m_dio->write("please enter a message");
    string downloadPath(m_dio->read());
    m_thisClassifier->downloadResults(downloadPath);
}

void DownloadCommand::execute(string downloadPath) {
    m_thisClassifier->downloadResults(downloadPath);
}
void DownloadCommand::activate(DownloadCommand* ptr, int& curr_threads, string downloadPath) {
    curr_threads++;
    ptr->execute(downloadPath);
    curr_threads--;
}
