#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "container.h"

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

    void ParseRow(vector<string>& row);
    void InitFromRow(vector<string>& row);
    void RangeCheck(size_t x, size_t y);
public:
    Inventory(){}
    // initializes from file, throws exception when the file is invalid
    Inventory (const string& file_path);
    bool EmptyCoordinate(size_t x, size_t y);
    bool FullCoordinate(size_t x, size_t y);
    // pushes container to (x,y) throws error if out of bounds or cannot push more
    bool PushContainer(size_t x, size_t y, Container& c);
    // pops container from (x,y) throws error if out of bounds or cannot pop more
    Container PopContainer(size_t x, size_t y);
    size_t GetNumFloors(){ return maxFloors;}
    size_t GetCoordinateHeight(size_t x, size_t y){ return storage[y][x].size();}
    pair<size_t, size_t> GetDimensions(){ return dimensions; }
    vector<Container> GetAllContainers();
};

#endif /* INVENTORY_H */
