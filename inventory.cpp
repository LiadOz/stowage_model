#include <iostream>
#include <fstream>
#include <sstream>
#include "inventory.h"
#include "util.h"

using std::ifstream;
using std::stringstream;

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
        logError("Initilization", "Too much floors in input");
        floors = maxFloors;
    }
    if(x > heights[0].size() || y > heights.size())
        logError("Initilization", "Cell outside of range");
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
bool Inventory::emptyCoordinate(size_t x, size_t y){
    if (storage[y][x].size() == 0) return true;
    return false;
}
bool Inventory::fullCoordinate(size_t x, size_t y){
    if (storage[y][x].size() == heights[y][x]) return true;
    return false;
}
bool Inventory::pushContainer(size_t x, size_t y, Container* c){
    if (fullCoordinate(x, y)){
        logError("insertion", "attempted to insert container in full space");
        return false;
    }
    storage[y][x].push_back(c);
    return true;
}
Container* Inventory::popContainer(size_t x, size_t y){
    if (emptyCoordinate(x, y)){
        logError("removal", "tried to remove non-existing cargo");
        return nullptr;
    }
    Container* c = storage[y][x].back();
    storage[y][x].pop_back();
    return c;
}
