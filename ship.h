#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>
#include "inventory.h"
#include "container.h"
#include "ShipRoute.h"

using std::vector;
using std::string;

class Ship {
private:
    size_t decks;
    Inventory storage;
public:
    // when you create a ship you supply the list of plans
    Ship(const string& file_path): storage(file_path){decks = storage.getNumFloors();}
    bool insertContainer(int x, int y, Container* c); // insertes container to (x,y)
    Container* removeContainer(int x, int y); // remove container from (x,y)
};

#endif /* SHIP_H */
