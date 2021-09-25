#pragma once
#include <string>
using namespace std;

class DefaultIO {
    public:
        virtual void write(string msg) = 0;
        virtual string read() = 0;
};