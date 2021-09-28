#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "QueueToSocketIO.h"
#include <pthread.h>
#include <stdlib.h>
#include "CLI.h"
#include <queue>
#include "SocketToQueue.h"

using namespace std;

void* readFromClient(void* argsptr) {
    Arguments* args = (Arguments*)(argsptr);
    while (*(args->isRunning)) {
        string data = args->dio->read();
        args->dio->write(data);
    }
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
    int i(0);

    //Searching for clients and binding them.
    int bindingReturned;
    while((bindingReturned = bind(sock, (struct sockaddr *) &sin, sizeof(sin))) >= 0) {
        //Listening to requests and handeling them.
        int listenReturned;
        while((listenReturned = listen(sock, 5))>=0) {

            //Accepting a client and saving its address.
            struct sockaddr_in client_sin;
            unsigned int addr_len = sizeof(client_sin);
            int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);

            if (client_sock < 0) {
                perror("error accepting client");
            }
            queue<string> q;
            SocketToQueue stq(client_sock, &q);
            bool running=true;
            Arguments argsSocketToQueue;
            argsSocketToQueue.isRunning = &running;
            argsSocketToQueue.dio = &stq;
            QueueToSocketIO qts(client_sock, &q);
            Arguments argsQueueToSocket;
            argsQueueToSocket.isRunning = &running;
            argsQueueToSocket.dio = &qts;

            pthread_t tidOfRead;
            pthread_attr_t attrOfRead;
            pthread_attr_init(&attrOfRead);
            pthread_create(&tidOfRead, &attrOfRead, readFromClient, &argsSocketToQueue);
            
            pthread_t tid;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_create(&tid, &attr, CLI::start, &argsQueueToSocket);
            i++;
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