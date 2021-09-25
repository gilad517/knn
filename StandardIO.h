#pragma once
#include <iostream>
#include "DefaultIO.h"
using namespace std;

class StandardIO : public DefaultIO{
    string read();
    void write(string msg);
};