#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "SocketIO.h"
using namespace std;

SocketIO::SocketIO(int clientSock) {
    m_clientSock = clientSock;
}

string SocketIO::read() {
    char buffer[65536]="";
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(m_clientSock, buffer, expected_data_len, 0);
    if(read_bytes>=0)
    {
        string received(buffer);
        return received;
    }
    return "A big Error happened";
}

void SocketIO::write(string msg) {
    char buffer[65536]="";
    int expected_data_len = msg.length()*sizeof(char)?msg.length()*sizeof(char):1;
    strcpy(buffer, msg.c_str());
    int sent_bytes = send(m_clientSock, buffer, expected_data_len, 0);
}

SocketIO::~SocketIO() {
    close(m_clientSock);
}