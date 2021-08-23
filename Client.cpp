#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

void getDataArray(char* data, string unclassifiedPath, string outputPath);

int main() {
    cout << "tcp server status: " << "not ready" << endl;
    cout << "udp server status: " << "not ready" << endl;
    
    const char* ip_address = "127.0.0.1";
    const int udp_port_no = 5555;
    const int tcp_port_no = 6666;

    struct sockaddr_in sin;
    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sock < 0) {
        perror("error creating socket");
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(tcp_port_no);

    if (connect(tcp_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }

    cout << "tcp server status: " << "ready" << endl;

    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock < 0) {
        perror("error creating socket");
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(udp_port_no);

    char message[] = "hello";
    int message_len = sizeof(message);

    int sent_bytes = sendto(udp_sock, message, message_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    int bytes = recvfrom(udp_sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    cout << "udp server status: " << buffer << endl;

    string protocol, unClassifiedPath, outputPath;
    cout<<"enter protocol, unclassified path, output path: ";
    cin>>protocol>>unClassifiedPath>>outputPath;
    char* data;
    getDataArray(data, unClassifiedPath, outputPath);
    char dataToSend[strlen(data) + 1];
    for (int i = 0; i < strlen(data) + 1; i++) {
        dataToSend[i] = data[i];
    }
    int dataLen = sizeof(dataToSend);
    while (true) {
        if (protocol.compare("UDP") == 0) {
            int sent_bytes = sendto(udp_sock, dataToSend, dataLen, 0, (struct sockaddr *) &sin, sizeof(sin));
            break;
        } else if (protocol.compare("TCP") == 0) {
            int sent_bytes = send(tcp_sock, dataToSend, dataLen, 0);
            if (sent_bytes < 0) {
            perror("error writing to server");
            }
            break;
        } else {
            cout<<"invalid protocol, please enter TCP/UDP"<<endl;
        }
        cin>>protocol;
    }


    close(tcp_sock);
    close(udp_sock);
    return 0;
}

void getDataArray(char* data, string unclassifiedPath, string outputPath) {
    int n = unclassifiedPath.length();
    char dataUnclassifiedPath[n + 1];
    strcpy(dataUnclassifiedPath, unclassifiedPath.c_str());
    int k = outputPath.length();
        char dataOutputPath[k + 1];
        strcpy(dataOutputPath, outputPath.c_str());
        char dataToSend[n + k + 2];
        for (int i = 0; i < n; i++) {
            dataToSend[i] = dataUnclassifiedPath[i];
        }
        dataToSend[n] = ' ';
        for (int i = n + 1; i < n + k + 1; i++) {
            dataToSend[i] = dataOutputPath[i - n - 1];
        }
        dataToSend[n + k + 1] = '\0';
        for (int i = 0; i < sizeof(dataToSend); i++) {
            data[i] = dataToSend[i];
        }
}