#pragma once

#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::ostream;
using std::vector;

#define CONTAINER_REGEX "[A-Z]{3}[U,J,Z]\\d{6}\\d"
#define ID_NUMBER_OF_LETTERS 4
#define PARSING_ID 0
#define PARSING_WEIGHT 1
#define PARSING_PORT 2

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
    // construct vector from a line
    Container(vector<string>& line);
    friend ostream& operator<<(ostream& out, const Container &c);
    int getWeight(){ return weight; }
    const string& getDestination() const { return destination; }
    const string& getId() const { return id; }
};
