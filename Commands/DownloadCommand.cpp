#include "DownloadCommand.hpp"

DownloadCommand::DownloadCommand(DefaultIO* thisIO) {
    m_dio = thisIO;
    m_description = "download results";
    m_thisClassifier = nullptr;
}
void DownloadCommand::execute() {
    string downloadPath(m_dio->read());
    m_thisClassifier->downloadResults(downloadPath);
}