#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include "inventory.h"
#include "util.h"

using std::ifstream;
using std::stringstream;
using std::out_of_range;

#define PARSING_WORDS 3
#define PARSING_DEPTH 0
#define PARSING_X 1 
#define PARSING_Y 2
#define X_POSITION 0
#define Y_POSITION 1
#define FLOORS 2

// initialize the size of the arrays
void Inventory::initFromRow(vector<size_t> row){
    maxFloors = row[PARSING_DEPTH];
    dimensions = {row[PARSING_X], row[PARSING_Y]};
    heights = vector<vector<size_t>>(
            row[PARSING_Y],
            vector<size_t>(row[PARSING_X], 0)
            );
    storage = vector<vector<vector<Container*>>>(
            row[PARSING_Y],
            vector<vector<Container*>>(row[PARSING_X])
            );
}

// writes the height of each (x,y)
void Inventory::parseRow(vector<size_t> row){
    size_t floors = row[FLOORS], x = row[X_POSITION], y = row[Y_POSITION];
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
    string line, data;
    bool firstRow = true;

    while(getline(file, line)){
        if(line[0] == '#') continue;
        vector<size_t> row;
        stringstream s(line);

        for (int i = 0; i < PARSING_WORDS; ++i) {
            getline(s, data, ',');
            row.push_back(std::stoi(data));
        }

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
