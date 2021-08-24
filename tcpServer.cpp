#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Classifier.h"

using namespace std;

int main() {

    const int server_port = 4444;
    const string classifiedPath = "/home/ori777/knn/files/classified.csv";
    int k(5);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }

    int listenReturned;
    while((listenReturned = listen(sock, 5))>=0) {
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);

        if (client_sock < 0) {
            perror("error accepting client");
        }

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
            string stringMsg(buffer);
            Classifier cls(classifiedPath);
            int spacePlace(stringMsg.find(' '));
            string unclassified(stringMsg.substr(0,spacePlace)), output(stringMsg.substr(spacePlace+1, stringMsg.length()));
            cls.Classify(unclassified, output,k);
            cout<<"classified successfully"<<endl;
        }
    }
    if (listenReturned < 0) {
        perror("error listening to a socket");
    }

    close(sock);


    return 0;
}