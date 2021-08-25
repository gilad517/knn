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
/// The main method of the udp server is used to establish the server and handeling client requests.
/// It first creates a new server socket and then searches for any client requests.
/// Given a request, the server either classifies the unclassified file to the wanted output
/// file using the Classifier class, and prints a "classified successfully" message,
/// or lets the client know the server is established, depending on the request. 
/// The server then keeps searching for more client requests.
/// </summary>
int main() {

    //The path to your classified Iris file, please make sure it is up to date before running the server.
    const string classifiedPath = "/home/ori777/knn/files/classified.csv";
    //Using port number 5454 and k=5 as agreed upon in the assignment.
    const int server_port = 5454;
    int k(5);
    
    //Creating a server udp socket.
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
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
        struct sockaddr_in from;
        unsigned int from_len = sizeof(struct sockaddr_in);
        char buffer[4096];
        int bytes;
        while((bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len)) >= 0)
        {
            //If the request is "hello" then the server sends "ready" to notify the client the server is up.
            //Otherwise(the request is to classify) the server Classifies the unclassified file to the wanted output file.
            //The server then keeps listening to other requests.
            string stringMsg(buffer);
            if(stringMsg.compare("hello") == 0)
            {
                stringMsg = "ready";
            } else {
                Classifier cls(classifiedPath);
                int spacePlace(stringMsg.find(' '));
                string unclassified(stringMsg.substr(0,spacePlace)), output(stringMsg.substr(spacePlace+1, stringMsg.length()));
                cls.Classify(unclassified, output,k);
                cout<<"classified successfully"<<endl;
                continue;
            }
            char* msg(&stringMsg[0]);
            int sent_bytes = sendto(sock, msg, bytes, 0, (struct sockaddr *) &from, sizeof(from));
            if (sent_bytes < 0) {
                perror("error writing to socket");
            }

            memset(buffer, 0, sizeof(buffer));

        }
        if (bytes < 0) {
            perror("error reading from socket");
            return 1;
        }
    }
    if (bindingReturned < 0) {
        perror("error binding to socket");
    }

    //Closing the server socket.
    close(sock);

    return 0;
}