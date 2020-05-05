#include "inventory.h"

#include <stdexcept>
#include "exceptions.h"
#include <cmath>
#include "util.h"
#include "parser.h"

using std::out_of_range;
using std::runtime_error;
using std::stoi;
using std::to_string;

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
        if (row.size() < 3) throw std::exception();
        depth = std::stoi(row[PARSING_DEPTH]); 
        x = stoi(row[PARSING_X]);
        y = stoi(row[PARSING_Y]);
    }catch(std::exception& e) {
        throw Error("Cannot read first line of ship plan", ERROR_BAD_PLAN_FILE);
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
    int floors, x, y;
    try {
        if (row.size() < 3) throw std::exception();
        floors = std::stoi(row[FLOORS]); 
        x = stoi(row[X_POSITION]);
        y = stoi(row[Y_POSITION]);
    }catch(std::exception& e) {
        LOG.LogError("Cannot read coordinate");
        errorVar(errorStatus, ERROR_BAD_FORMAT);
        return;
    }
    string logCoordinate = "(" + to_string(x) + ", " + to_string(y) + ")";
    if(floors >= (int)maxFloors){
        LOG.LogError("Too much floors in input");
        errorVar(errorStatus, ERROR_FLOOR_OVERFLOW);
        return;
    }
    if(x > (int)heights[0].size() || y > (int)heights.size() || x < 0 || y < 0){
        LOG.LogError("Coordinate outside of range");
        errorVar(errorStatus, ERROR_XY_EXCEEDED);
        return;
    }
    // prevent duplicate (x,y)
    if(heights[y][x]) {
        LOG.LogError("Duplicate coordinate found");
        if((int)heights[y][x] == floors)
            errorVar(errorStatus, ERROR_BAD_FORMAT);
        else
            errorVar(errorStatus, ERROR_XY_EXCEEDED);
        return;
    }
    else heights[y][x] = floors;
}

int Inventory::ReadPlan(const string& file_path){
    Parser parse;
    try {
        parse.LoadFile(file_path);
    }catch(runtime_error& e) {
        throw Error("Invalid ship plan file", ERROR_BAD_PLAN_FILE);
    }

    bool firstRow = true;
    while(parse.Good()){
        vector<string> row;
        parse>>row;

        // parsing the first row
        if(firstRow){
            InitFromRow(row);
            firstRow = false;
        }
        // parsing each (x,y)
        else ParseRow(row);
    }
    return errorStatus;
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
    if (storage[y][x].size() == heights[y][x] - 1) return true;
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
