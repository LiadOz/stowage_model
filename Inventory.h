#pragma once 

#include <vector>
#include <string>

#include "Container.h"

using std::vector;
using std::string;
using std::pair;

// represents the ship plan and allows storing containers
class Inventory {
private:
    size_t maxFloors;
    vector<vector<size_t>> heights;
    vector<vector<vector<Container>>> storage;
    pair<size_t, size_t> dimensions;
    int errorStatus = 0;

    void parseRow(vector<string>& row);
    void initFromRow(vector<string>& row);
    void rangeCheck(size_t x, size_t y);
public:
    Inventory(){}
    // initializes from file, throws exception when the file is invalid
    int readPlan(const string& filePath);
    Inventory (const string& file_path);
    bool emptyCoordinate(size_t x, size_t y);
    bool fullCoordinate(size_t x, size_t y);
    // pushes container to (x,y) throws error if out of bounds or cannot push more
    bool pushContainer(size_t x, size_t y, Container& c);
    // pops container from (x,y) throws error if out of bounds or cannot pop more
    Container popContainer(size_t x, size_t y);
    size_t getNumFloors(){ return maxFloors;}
    size_t getCoordinateHeight(size_t x, size_t y);
    size_t getCoordinateDepth(size_t x, size_t y);
    pair<size_t, size_t> getDimensions(){ return dimensions; }
    vector<Container> getAllContainers();
};
