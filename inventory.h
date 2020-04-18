#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "container.h"
using std::vector;
using std::string;
using std::pair;

class Inventory {
private:
    size_t maxFloors;
    vector<vector<size_t>> heights;
    vector<vector<vector<Container*>>> storage;
    pair<size_t, size_t> dimensions;

    void parseRow(vector<size_t> row);
    void initFromRow(vector<size_t> row);
    void rangeCheck(size_t x, size_t y);
public:
    Inventory(){}
    Inventory (const string& file_path);
    bool emptyCoordinate(size_t x, size_t y);
    bool fullCoordinate(size_t x, size_t y);
    bool pushContainer(size_t x, size_t y, Container* c);
    Container* popContainer(size_t x, size_t y);
    size_t getNumFloors(){ return maxFloors;}
    size_t getCoordinateHeight(size_t x, size_t y){ return storage[y][x].size();}
    pair<size_t, size_t> getDimensions(){ return dimensions; }
};

#endif /* INVENTORY_H */
