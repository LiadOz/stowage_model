#include "Inventory.h"

#include <stdexcept>
#include <cmath>

#include "Exceptions.h"
#include "Util.h"
#include "Parser.h"

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
void Inventory::initFromRow(vector<string>& row){
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
void Inventory::parseRow(vector<string>& row){
    int floors, x, y;
    try {
        if (row.size() < 3) throw std::exception();
        floors = std::stoi(row[FLOORS]); 
        x = stoi(row[X_POSITION]);
        y = stoi(row[Y_POSITION]);
    }catch(std::exception& e) {
        LOG.logError("Cannot read coordinate");
        errorVar(errorStatus, ERROR_BAD_FORMAT);
        return;
    }
    string logCoordinate = "(" + to_string(x) + ", " + to_string(y) + ")";
    if(floors >= (int)maxFloors){
        LOG.logError("Too much floors in input");
        errorVar(errorStatus, ERROR_FLOOR_OVERFLOW);
        return;
    }
    if(x > (int)heights[0].size() || y > (int)heights.size() || x < 0 || y < 0){
        LOG.logError("Coordinate outside of range");
        errorVar(errorStatus, ERROR_XY_EXCEEDED);
        return;
    }
    // prevent duplicate (x,y)
    if(heights[y][x]) {
        LOG.logError("Duplicate coordinate found");
        if((int)heights[y][x] == floors)
            errorVar(errorStatus, ERROR_BAD_FORMAT);
        else
            errorVar(errorStatus, ERROR_XY_EXCEEDED);
        return;
    }
    else heights[y][x] = floors;
}

int Inventory::readPlan(const string& file_path){
    Parser parse;
    try {
        parse.loadFile(file_path);
    }catch(runtime_error& e) {
        throw Error("Invalid ship plan file", ERROR_BAD_PLAN_FILE);
    }

    bool firstRow = true;
    while(parse.good()){
        vector<string> row;
        parse>>row;

        // parsing the first row
        if(firstRow){
            initFromRow(row);
            firstRow = false;
        }
        // parsing each (x,y)
        else parseRow(row);
    }
    return errorStatus;
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
    if (storage[y][x].size() == heights[y][x] - 1) return true;
    return false;
}
bool Inventory::pushContainer(size_t x, size_t y, Container& c){
    rangeCheck(x, y);
    if (fullCoordinate(x, y))
        throw out_of_range("Coordinate is full");
    storage[y][x].push_back(c);
    return true;
}

Container Inventory::popContainer(size_t x, size_t y){
    rangeCheck(x, y);
    if (emptyCoordinate(x, y))
        throw out_of_range("Coordinate is empty");
    Container c = storage[y][x].back();
    storage[y][x].pop_back();
    return c;
}

vector<Container> Inventory::getAllContainers(){
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
