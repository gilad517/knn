#pragma once
#include "SettingsCommand.hpp"

class SettingsCommand : public Command{
    SettingsCommand(DefaultIO* thisIO) {
        m_dio = thisIO;
        m_description = "algorithm settings";
        m_thisClassifier = nullptr;
    }
    void execute() {
        string msg = "The current KNN parameters are: K = ";
        msg+=to_string(m_thisClassifier->getK());
        msg+=", distance metric = ";
        DistanceMetric metric = m_thisClassifier->getMetric();
        if(metric == DistanceMetric::EUC) {
            msg+="EUC";
        } else if(metric == DistanceMetric::CHE) {
            msg+="CHE";
        } else{
            msg+="MAN";
        }
        m_dio->write(msg);
        bool isValid = true;
        do
        {
            string input(m_dio->read());
            size_t spacePlace = input.find(' ');
            if(spacePlace == string::npos) {
                isValid = false;
                m_dio->write("invalid value for distance metric");
            } else {
                string kStr(input.substr(0,spacePlace)), metricStr(input.substr(spacePlace + 1, input.length()));
                if(!isInt(kStr)) {
                    isValid = false;
                    m_dio->write("invalid value for K");
                } else if (!((metricStr.compare("EUC") == 0) || (metricStr.compare("CHE") == 0)|| (metricStr.compare("MAN") == 0))) {
                    m_dio->write("invalid value for distance metric");
                    isValid = false;
                } else {
                    isValid = true;
                    m_thisClassifier->setK(stoi(kStr));
                    DistanceMetric mtr;
                    if(metricStr.compare("EUC") == 0){
                        mtr = DistanceMetric::EUC;
                    } else if(metricStr.compare("CHE") == 0) {
                        mtr = DistanceMetric::CHE;
                    } else {
                        mtr = DistanceMetric::MAN;
                    }
                    m_thisClassifier->setMetric(mtr);
                }
            }
        } while (!isValid);
    }
};

bool isInt(string str) {
    string::const_iterator it = str.begin();
    while (it != str.end() && isdigit(*it)) {
        ++it;
    }
    return !str.empty() && it == str.end();
}