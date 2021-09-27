#include "DownloadCommand.h"

DownloadCommand::DownloadCommand(DefaultIO* thisIO) {
    m_dio = thisIO;
    m_description = "download results";
    m_thisClassifier = nullptr;
}
void DownloadCommand::execute() {
    string downloadPath(m_dio->read());
    m_thisClassifier->downloadResults(downloadPath);
}

void* DownloadCommand::executeInThread(void* par) {
    this->execute();
}