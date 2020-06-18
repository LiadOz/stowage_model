#pragma once 

#include <vector>
#include <string>

#include "Container.h"

using std::vector;
using std::string;
using std::pair;

#define PARSING_WORDS 3
#define PARSING_DEPTH 0
#define PARSING_X 1 
#define PARSING_Y 2
#define X_POSITION 0
#define Y_POSITION 1
#define FLOORS 2

// represents the ship plan and allows storing containers
class Inventory {
private:
    size_t maxFloors;
    int maxCapacity = 0;
    int currentCapacity = 0;
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
    Container peekContainer(size_t x, size_t y);
    size_t getNumFloors(){ return maxFloors;}
    size_t getCoordinateHeight(size_t x, size_t y);
    int getCoordinateDepth(size_t x, size_t y);
    // used to find if a certain coordinate has a container with specific destinaion if it doesn't -1 is returned else it returns the number of containers above it.
    int getContainerDestinationLevel(size_t x, size_t y, const string& port);
    pair<size_t, size_t> getDimensions(){ return dimensions; }
    vector<Container> getAllContainers();
    vector<Container> getCoordinateContainers(int x, int y){ return storage[y][x]; }

    int freeSpaces() { return maxCapacity - currentCapacity;}
};
