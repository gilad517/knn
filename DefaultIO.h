#pragma once
#include <string>
using namespace std;
/**
 * @brief The DefaultIO interface represents an abstract way of io communication.
 * 
 */
class DefaultIO {
    public:

        /**
         * @brief A purely abstract method for outputing a certain string
         * 
         * @param msg The string to output
         */
        virtual void write(string msg) = 0;

        /**
         * @brief A purely abstract method for receiving an input string
         * 
         * @return string The input string received.
         */
        virtual string read() = 0;
};