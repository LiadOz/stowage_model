#ifndef CONTAINER_H
#define CONTAINER_H

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
    int GetWeight(){ return weight; }
    string GetDestination(){ return destination; }
    string GetId(){ return id; }
};

#endif /* CONTAINER_H */
