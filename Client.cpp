#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "SocketIO.h"
#include "StandardIO.h"

using namespace std;

/**
 * @brief The main method of the client 
 * seeking an available server, and(if found) establishes connection and begins communication.
 * @return int A generic numeric output to indicate errors
 */
int main() {
    //The ip adress of this machine(the local machine is always 127.0.0.1 ip).
    const char* ip_address = "127.0.0.1";
    //Using port number 4444 for tcp.
    const int tcp_port_no = 4444;

    struct sockaddr_in sin;
    //Building the tcp socket.
    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sock < 0) {
        perror("error creating tcp socket");
        return 1;
    }

    //Initializing to the tcp address.
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(tcp_port_no);

    //Trying to connect to the tcp server.
    if (connect(tcp_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to tcp server");
        return 1;
    }

    SocketIO client(tcp_sock);
    DefaultIO* dio;
    StandardIO sio;
    dio = &sio;
    string msg;
    do
    {
        msg=client.read();
        if((msg.compare("please enter a message") == 0)) {
            client.write(dio->read());
        } else if (msg.compare("refuse connection") == 0) {
            dio->write("server refused connection");
            break;
        } else if (msg.compare("terminate") != 0) {
            dio->write(msg);
        }
    } while (msg.compare("terminate")!=0);
    
    return 0;
}