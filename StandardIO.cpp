#include <iostream>
#include "StandardIO.h"
using namespace std;


string StandardIO::read() {
    string msg;
    getline(cin, msg);
    return msg;
}

void StandardIO::write(string msg) {
    cout<<msg<<endl;
}