#pragma once
#include <iostream>
#include "DefaultIO.h"
#include <string>
using namespace std;

/**
 * @brief The SocketIO class is a way of io communication using sockets.
 * implements the DefaultIO interface.
 */
class SocketIO : public DefaultIO {
    private:
        //The client socket.
        int m_clientSock;
    public:

        /**
         * @brief Construct a new SocketIO object given the client socket.
         * 
         * @param clientSock The client socket.
         */
        SocketIO(int clientSock);
        
        //inherited methods from the DefaultIO interface.
        string read();
        void write(string msg);

        /**
         * @brief Destroy the Socket IO object
         * 
         */
        ~SocketIO();
};