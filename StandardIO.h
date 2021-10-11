#pragma once
#include <iostream>
#include "DefaultIO.h"
using namespace std;

/**
 * @brief The StandardIO class is a way of io communication using standard cout cin io.
 * implements the DefaultIO interface.
 */
class StandardIO : public DefaultIO {

    //inherited methods from the DefaultIO interface.
    string read();
    void write(string msg);
};