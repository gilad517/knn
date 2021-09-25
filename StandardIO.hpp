#include <iostream>
#include "DefaultIO.hpp"
using namespace std;

class StandardIO : public DefaultIO{
    string read();
    void write(string msg);
};