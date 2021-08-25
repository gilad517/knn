#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

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
    //Using port number 5454 for udp and 4444 for tcp.
    const int udp_port_no = 5454;
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

    cout << "tcp server status: " << "ready" << endl;

    //Building the udp socket.
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock < 0) {
        perror("error creating udp socket");
        return 1;
    }
    
    //Initializing to the udp address.
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(udp_port_no);

    //The agreed message to send to the udp server to get its approval of the connection.
    char message[] = "hello";
    int message_len = sizeof(message);

    //Trying to send the message to the udp server.
    int sent_bytes = sendto(udp_sock, message, message_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to udp socket");
        return 1;
    }

    //Trying to receive the agreed message from the udp server to approve of the connection.
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    int bytes = recvfrom(udp_sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from udp socket");
        return 1;
    }
    string received(buffer);
    if(received.compare("ready") == 0){
        cout << "udp server status: ready" << endl;
    } else {
        cout<< "udp server status: not ready" <<endl;
        cout<< "was sent " << received<<endl;
    }
    
    //Receiving the user input and sending the wanted message to the wanted server.
    string protocol, unClassifiedPath, outputPath;
    cout<<"enter protocol, unclassified path, output path: ";
    cin>>protocol>>unClassifiedPath>>outputPath;
    string stringDataToSend = unClassifiedPath + " " + outputPath;
    char* dataToSend(&stringDataToSend[0]);
    int dataLen = strlen(dataToSend);
    while (true) {
        if (protocol.compare("UDP") == 0) {
            int sent_bytes = sendto(udp_sock, dataToSend, dataLen, 0, (struct sockaddr *) &sin, sizeof(sin));
            if (sent_bytes < 0) {
                perror("error writing to udp server");
                return 1;
            }
            break;
        } else if (protocol.compare("TCP") == 0) {
            int sent_bytes = send(tcp_sock, dataToSend, dataLen, 0);
            if (sent_bytes < 0) {
                perror("error writing to tcp server");
                return 1;
            }
            break;
        } else {
            cout<<"invalid protocol, please enter TCP/UDP"<<endl;
        }
        cin>>protocol;
    }

    //Closing the server sockets.
    close(tcp_sock);
    close(udp_sock);
    return 0;
}