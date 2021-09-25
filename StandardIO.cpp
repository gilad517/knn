#include <iostream>
#include "StandardIO.hpp"
using namespace std;


string StandardIO::read() {
    string msg;
    cin>>msg;
    return msg;
}

void StandardIO::write(string msg) {
    cout<<msg<<endl;
}