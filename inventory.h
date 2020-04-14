#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "container.h"
using std::vector;
using std::string;

class Inventory {
private:
    size_t maxFloors;
    vector<vector<size_t>> heights;
    vector<vector<vector<Container*>>> storage;

    void parseRow(vector<size_t> row);
    void initFromRow(vector<size_t> row);
public:
    Inventory (const string& file_path);
    bool emptyCoordinate(size_t x, size_t y);
    bool fullCoordinate(size_t x, size_t y);
    bool pushContainer(size_t x, size_t y, Container* c);
    Container* popContainer(size_t x, size_t y);
    size_t getNumFloors(){ return maxFloors;}
};

#endif /* INVENTORY_H */
