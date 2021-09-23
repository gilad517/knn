#pragma once
#include "DownloadCommand.hpp"

class DownloadCommand : public Command{
    DownloadCommand(DefaultIO* thisIO) {
        m_dio = thisIO;
        m_description = "download results";
        m_thisClassifier = nullptr;
    }
    void execute() {
        string downloadPath(m_dio->read());
        m_thisClassifier->downloadResults(downloadPath);
    }
};