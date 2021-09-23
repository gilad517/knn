#include <iostream>
#include "DefaultIO.hpp"
using namespace std;

class StandardIO : public DefaultIO{
    string read() {
        string msg;
        cin>>msg;
        return msg;
    }
    
    void write(string msg){
        cout<<msg<<endl;
    }
};