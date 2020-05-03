#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include "inventory.h"
#include "util.h"
#include "parser.h"

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
void Inventory::InitFromRow(vector<string>& row){
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
    storage = vector<vector<vector<Container>>>(y,
            vector<vector<Container>>(x)
            );
}

// writes the height of each (x,y)
void Inventory::ParseRow(vector<string>& row){
    size_t floors, x, y;
    try {
        floors = std::stoi(row[FLOORS]); 
        x = stoi(row[X_POSITION]);
        y = stoi(row[Y_POSITION]);
    }catch(std::exception& e) {
        throw runtime_error("Parsed string instead of int in plan file");
    }
    if(floors > maxFloors){
        Logger::Instance().LogError("Too much floors in input");
        floors = maxFloors;
    }
    if(x > heights[0].size() || y > heights.size())
        Logger::Instance().LogError("Cell outside of range");
    else heights[y][x] = floors;
}

Inventory::Inventory(const string& file_path){
    Parser parse;
    try {
        parse.LoadFile(file_path);
    }catch(runtime_error& e) {
        throw runtime_error("Invalid ship plan file");
    }

    bool firstRow = true;
    while(parse.Good()){
        vector<string> row;
        parse>>row;
        if(row.size() < PARSING_WORDS)
            throw runtime_error("Invalid ship plan format");
        // parsing the first row
        if(firstRow){
            InitFromRow(row);
            firstRow = false;
        }
        // parsing each (x,y)
        else ParseRow(row);
    }
}

// test the range of (x, y) if it's outside throws out_of_range error
void Inventory::RangeCheck(size_t x, size_t y){
    if (x >= dimensions.first || y >= dimensions.second)
        throw out_of_range("Attempted to access invalid location");
}
bool Inventory::EmptyCoordinate(size_t x, size_t y){
    RangeCheck(x, y);
    if (storage[y][x].size() == 0) return true;
    return false;
}
bool Inventory::FullCoordinate(size_t x, size_t y){
    RangeCheck(x, y);
    if (storage[y][x].size() == heights[y][x]) return true;
    return false;
}
bool Inventory::PushContainer(size_t x, size_t y, Container& c){
    RangeCheck(x, y);
    if (FullCoordinate(x, y))
        throw out_of_range("Coordinate is full");
    storage[y][x].push_back(c);
    return true;
}

Container Inventory::PopContainer(size_t x, size_t y){
    RangeCheck(x, y);
    if (EmptyCoordinate(x, y))
        throw out_of_range("Coordinate is empty");
    Container c = storage[y][x].back();
    storage[y][x].pop_back();
    return c;
}

vector<Container> Inventory::GetAllContainers(){
    vector<Container> l;
    for (auto& vv : storage) {
        for (auto& v : vv) {
            for (auto& c : v) {
                l.push_back(c);
            }
        }
    }
    return l;
}
