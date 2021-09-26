#pragma once
#include <iostream>
#include "DefaultIO.h"
#include "SocketIO.h"
#include <string>
#include <queue>
using namespace std;

class QueueToSocketIO : public DefaultIO {
    private:
        SocketIO* m_sockIO;
        queue<string>* m_q;
    public:
        QueueToSocketIO(int clientSock, queue<string>* q);
        string read();
        void write(string msg);
        ~QueueToSocketIO();
};