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

/// <summary>
/// The main method is used by the user to classify an unclassified Iris file.
/// it first establishes and checks connection to both udp and tcp servers and then(if connected)
/// asks the user to enter the server format of the user's choice, and then (after a space)
/// the path to the unclassified Iris file, and then (after a space) the path to the output file.
/// The wanted server should then classify the unclassified Iris file to the output file
/// and print a "classified successfully" message.
/// </summary>
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
        } else if (msg.compare("terminate") != 0) {
            dio->write(msg);
        }
    } while (msg.compare("terminate")!=0);
    


    delete &client;
    return 0;
}