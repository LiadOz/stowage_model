#pragma once

#include <string>
#include <iostream>

using std::string;
using std::ostream;

// class which represnts each container
class Container {
private:
    int weight;
    string destination;
    string id;

public:
    // throws invalid argument if destination or id are not 
    // according to format
    Container(int weight, const string& destination, const string& id);
    friend ostream& operator<<(ostream& out, const Container &c);
    int getWeight(){ return weight; }
    string getDestination(){ return destination; }
    string getId(){ return id; }
};
