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
#include "SocketIO.h"
#include <time.h>
#include <ctime>
using namespace std;

void acceptAndHandleClient(int server_sock, int& curr_threads) {
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
    CLI::start(dio, curr_threads);
}

/// <summary>
/// The main method of the tcp server is used to establish the server and handeling client requests.
/// It first creates a new server socket and then searches for any client requests.
/// Given a request, the server classifies the unclassified file to the wanted output
/// file using the Classifier class, prints a "classified successfully" message, and keeps searching for more clients.
/// </summary>
void activateServer(int sock, clock_t& lastUserConnected, bool& shouldAccept, int& curr_threads) {
    //Using port number 4444 and k=5 as agreed upon in the assignment.
    const int server_port = 4444;
    //Creating and initializing a sockaddr_in member for the server.
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    //Searching for clients and binding them.
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) { 
        perror("error binding socket");
    }
    //Listening to requests and handeling them.
    int listenReturned;
    while(((listenReturned = listen(sock, 5)) >= 0) && shouldAccept) {
        lastUserConnected = clock();
        thread thrd(acceptAndHandleClient, sock, ref(curr_threads));
        thrd.detach();
    }
    if (listenReturned < 0) {
        perror("error listening to a socket");
    }
}

int main(int argc, char const *argv[])
{
    //timeout variables
    clock_t lastUserConnected;
    bool shouldAccept = true;
    int curr_threads = 0;
    int secondOfTimeOut = 50;

    //Creating a server tcp socket.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    lastUserConnected = clock();
    thread server(activateServer, sock, ref(lastUserConnected),ref(shouldAccept), ref(curr_threads));
    while (float(clock() - lastUserConnected)/CLOCKS_PER_SEC < secondOfTimeOut) {
        this_thread::sleep_for(chrono::milliseconds(1000));
    } 
    shouldAccept = false;
    while (curr_threads) {
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    close(sock);
    return 0;
}
