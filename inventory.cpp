#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include "inventory.h"
#include "util.h"

using std::ifstream;
using std::stringstream;
using std::out_of_range;
using std::runtime_error;
using std::stoi;

#define PARSING_WORDS 3
#define PARSING_DEPTH 0
#define PARSING_X 1 
#define PARSING_Y 2
#define X_POSITION 0
#define Y_POSITION 1
#define FLOORS 2

// initialize the size of the arrays
void Inventory::initFromRow(vector<string> row){
    size_t depth, x, y;
    try {
        depth = std::stoi(row[PARSING_DEPTH]); 
        x = stoi(row[PARSING_X]);
        y = stoi(row[PARSING_Y]);
    }catch(std::exception& e) {
        throw runtime_error("Parsed string instead of int in plan file");
    }
    maxFloors = depth;
    dimensions = {x, y};
    heights = vector<vector<size_t>>(y, vector<size_t>(x, 0)
            );
    storage = vector<vector<vector<Container*>>>(y,
            vector<vector<Container*>>(x)
            );
}

// writes the height of each (x,y)
void Inventory::parseRow(vector<string> row){
    size_t floors, x, y;
    try {
        floors = std::stoi(row[FLOORS]); 
        x = stoi(row[X_POSITION]);
        y = stoi(row[Y_POSITION]);
    }catch(std::exception& e) {
        throw runtime_error("Parsed string instead of int in plan file");
    }
    if(floors > maxFloors){
        Logger::Instance().logError("Too much floors in input");
        floors = maxFloors;
    }
    if(x > heights[0].size() || y > heights.size())
        Logger::Instance().logError("Cell outside of range");
    else heights[y][x] = floors;
}

Inventory::Inventory(const string& file_path){
    ifstream file(file_path);
    if(!file.good()){
        throw runtime_error("Invalid ship plan file");
    }
    string line, data;
    bool firstRow = true;

    while(getline(file, line)){
        if(isCommentLine(line)) continue;
        vector<string> row = getDataFromLine(line, PARSING_WORDS);

        // parsing the first row
        if(firstRow){
            initFromRow(row);
            firstRow = false;
        }
        // parsing each (x,y)
        else parseRow(row);
    }

    file.close();
}

// test the range of (x, y) if it's outside throws out_of_range error
void Inventory::rangeCheck(size_t x, size_t y){
    if (x >= dimensions.first || y >= dimensions.second)
        throw out_of_range("Attempted to access invalid location");
}
bool Inventory::emptyCoordinate(size_t x, size_t y){
    rangeCheck(x, y);
    if (storage[y][x].size() == 0) return true;
    return false;
}
bool Inventory::fullCoordinate(size_t x, size_t y){
    rangeCheck(x, y);
    if (storage[y][x].size() == heights[y][x]) return true;
    return false;
}
bool Inventory::pushContainer(size_t x, size_t y, Container* c){
    rangeCheck(x, y);
    if (fullCoordinate(x, y))
        throw out_of_range("Coordinate is full");
    storage[y][x].push_back(c);
    return true;
}
Container* Inventory::popContainer(size_t x, size_t y){
    rangeCheck(x, y);
    if (emptyCoordinate(x, y))
        throw out_of_range("Coordinate is empty");
    Container* c = storage[y][x].back();
    storage[y][x].pop_back();
    return c;
}

vector<Container> Inventory::getAllContainers(){
    vector<Container> l;
    for (auto& vv : storage) {
        for (auto& v : vv) {
            for (auto& c : v) {
                l.push_back(*c);
            }
        }
    }
    return l;
}
