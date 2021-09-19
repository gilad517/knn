#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Classifier.h"

using namespace std;

/// <summary>
/// The main method of the tcp server is used to establish the server and handeling client requests.
/// It first creates a new server socket and then searches for any client requests.
/// Given a request, the server classifies the unclassified file to the wanted output
/// file using the Classifier class, prints a "classified successfully" message, and keeps searching for more clients.
/// </summary>
int main() {

    //The path to your classified Iris file, please make sure it is up to date before running the server.
    const string classifiedPath = "/home/gilad517/knn/knn/files/classified.csv";
    //Using port number 4444 and k=5 as agreed upon in the assignment.
    const int server_port = 4444;
    int k(5);

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
            //Accepting a client and saving its address.
            struct sockaddr_in client_sin;
            unsigned int addr_len = sizeof(client_sin);
            int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);

            if (client_sock < 0) {
                perror("error accepting client");
            }

            //Receiving request from client and handeling it.
            char buffer[4096];
            int expected_data_len = sizeof(buffer);
            int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
            if (read_bytes == 0) {
                // connection is closed
                continue;
            }
            else if (read_bytes < 0) {
                perror("error receiving from client");
            }
            else {
                //Classifing the unclassified file to the wanted output file.
                string stringMsg(buffer);
                Classifier cls(classifiedPath);
                int spacePlace(stringMsg.find(' '));
                string unclassified(stringMsg.substr(0,spacePlace)), output(stringMsg.substr(spacePlace+1, stringMsg.length()));
                cls.Classify(unclassified);
                cout << cls.downloadResults(output);
                cout << cls.displayResults();
                cout<<"classified successfully"<<endl;
                break;
            }
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