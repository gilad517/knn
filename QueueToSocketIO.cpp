#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "QueueToSocketIO.h"
using namespace std;

QueueToSocketIO::QueueToSocketIO(int clientSock,  queue<string>* q) {
    m_sockIO = new SocketIO(clientSock);
    m_q = q;
}

string QueueToSocketIO::read() {
    string toReturn(m_q->front());
    m_q->pop();
    return toReturn;
}

void QueueToSocketIO::write(string msg) {
    m_sockIO->write(msg);
}

QueueToSocketIO::~QueueToSocketIO() {
    delete m_sockIO;
}