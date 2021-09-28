#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "DefaultIO.h"
#include <thread>
#include <stdlib.h>
#include "CLI.h"
#include <queue>
#include "SocketIO.h"

using namespace std;

void readFromClient(int server_sock) {
    //Accepting a client and saving its address.
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(server_sock, (struct sockaddr *) &client_sin,  &addr_len);
    
    if (client_sock < 0) {
        perror("error accepting client");
    }

    DefaultIO* dio;
    SocketIO sio(client_sock);
    dio = &sio;
    CLI::start(dio);
}

/// <summary>
/// The main method of the tcp server is used to establish the server and handeling client requests.
/// It first creates a new server socket and then searches for any client requests.
/// Given a request, the server classifies the unclassified file to the wanted output
/// file using the Classifier class, prints a "classified successfully" message, and keeps searching for more clients.
/// </summary>
int main() {
    //Using port number 4444 and k=5 as agreed upon in the assignment.
    const int server_port = 4444;

    //Creating a server tcp socket.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    //Creating and initializing a sockaddr_in member for the server.
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    
    //Searching for clients and binding them.
    int bindingReturned;
    while((bindingReturned = bind(sock, (struct sockaddr *) &sin, sizeof(sin))) >= 0) {
        //Listening to requests and handeling them.
        int listenReturned;
        while((listenReturned = listen(sock, 5))>=0) {
            thread thrd(readFromClient,sock);
            thrd.detach();
        }
        if (listenReturned < 0) {
            perror("error listening to a socket");
        }
    }
    if (bindingReturned < 0) {
        perror("error binding socket");
    }

    //Closing the server socket.
    close(sock);


    return 0;
}