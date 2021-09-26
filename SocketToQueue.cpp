#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "SocketToQueue.h"
using namespace std;

SocketToQueue::SocketToQueue(int clientSock,  queue<string>* q) {
    m_sockIO = new SocketIO(clientSock);
    m_q = q;
}

string SocketToQueue::read() {
    return m_sockIO->read();
}

void SocketToQueue::write(string msg) {
    m_q->push(msg);
}

SocketToQueue::~SocketToQueue() {
    delete m_sockIO;
}