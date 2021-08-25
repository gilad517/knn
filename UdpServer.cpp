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
    const string classifiedPath = "/home/ori777/knn/files/classified.csv";
    const int server_port = 5454;
    int k(5);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;

    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to socket");
    }

    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    int bytes;
    while((bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len)) >= 0)
    {
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
    close(sock);

    return 0;
}