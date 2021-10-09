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
#include <chrono>
#include <mutex>

#define now() std::chrono::high_resolution_clock::now()
#define duration(a) std::chrono::duration_cast<std::chrono::seconds>(a).count()

using namespace std;

typedef std::chrono::high_resolution_clock::time_point Time;

void acceptAndHandleClient(int server_sock, int& curr_threads, Time& lastUserConnected, bool& shouldAccept, pthread_mutex_t& muLock) {
    //Accepting a client and saving its address.
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    if (shouldAccept) {
        int client_sock = accept(server_sock, (struct sockaddr *) &client_sin,  &addr_len);
        if (client_sock < 0) {
            perror("error accepting client");
        }
        pthread_mutex_unlock(&muLock);

        DefaultIO* dio;
        SocketIO sio(client_sock);
        dio = &sio;
        if (shouldAccept) {
            lastUserConnected = now();
            CLI::start(dio, ref(curr_threads));
        } else {
            dio->write("refuse connection");
        }
    }
}

/// <summary>
/// The main method of the tcp server is used to establish the server and handeling client requests.
/// It first creates a new server socket and then searches for any client requests.
/// Given a request, the server classifies the unclassified file to the wanted output
/// file using the Classifier class, prints a "classified successfully" message, and keeps searching for more clients.
/// </summary>
void activateServer(int sock, Time& lastUserConnected, bool& shouldAccept, int& curr_threads) {
    //Using port number 4444.
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
    pthread_mutex_t muLock;
    if (pthread_mutex_init(&muLock, NULL) != 0)
    {
        perror("error creating mutex");
    }
    while(((listenReturned = listen(sock, 5)) >= 0) && shouldAccept) {
        pthread_mutex_lock(&muLock);
        thread thrd(acceptAndHandleClient, sock, ref(curr_threads), ref(lastUserConnected), ref(shouldAccept), ref(muLock));
        thrd.detach();
    }
    if (listenReturned < 0) {
        perror("error listening to a socket");
    }
    pthread_mutex_destroy(&muLock);
}

int main(int argc, char const *argv[])
{
    //timeout variables
    Time lastUserConnected;
    bool shouldAccept = true;
    int curr_threads = 0;
    int secondOfTimeOut = 30;

    //Creating a server tcp socket.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    lastUserConnected = now();
    thread server(activateServer, sock, ref(lastUserConnected),ref(shouldAccept), ref(curr_threads));
    server.detach();
    while (duration(now() - lastUserConnected) < secondOfTimeOut) {
        this_thread::sleep_for(chrono::seconds(max<int>(secondOfTimeOut - duration(now() - lastUserConnected), 1)));
    } 
    shouldAccept = false;
    cout << "no more connections - server time out" <<endl;
    while (curr_threads) {
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    close(sock);
    return 0;
}
