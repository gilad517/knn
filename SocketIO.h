#pragma once
#include <iostream>
#include "DefaultIO.h"
#include <string>
using namespace std;

class SocketIO : public DefaultIO {
    private:
        int m_clientSock;
    public:
        SocketIO(int clientSock);
        string read();
        void write(string msg);
        ~SocketIO();
};