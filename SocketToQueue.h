#pragma once
#include <iostream>
#include "DefaultIO.h"
#include "SocketIO.h"
#include <string>
#include <queue>
using namespace std;

class SocketToQueue : public DefaultIO {
    private:
        SocketIO* m_sockIO;
        queue<string>* m_q;
    public:
        SocketToQueue(int clientSock, queue<string>* q);
        string read();
        void write(string msg);
        ~SocketToQueue();
};