#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "inventory.h"
#include "container.h"

#define INVALID_ARG -1
using std::vector;
using std::string;
using std::pair;
using std::ofstream;

// used to log actions by the ship
class ShipLogger {
private:
    ofstream file;
public:
    void setLogFile(const string& file_path){ file.open(file_path);}
    void closeLogFile(){ file.close();}
    void logAction(const string& action);
};

class Ship {
private:
    size_t decks;
    Inventory storage;
    ShipLogger logger;
public:
    // when you create a ship you supply the list of plans
    Ship(){};
    Ship(const string& file_path): storage(file_path){decks = storage.getNumFloors();}
    size_t getCoordinateHeight(size_t x, size_t y){ return storage.getCoordinateHeight(x, y);}
    void insertContainer(size_t x, size_t y, Container* c); // insertes container to (x,y)
    // move container from (x1, y1) to (x2, y2)
    void moveContainer(size_t x1, size_t y1, size_t x2, size_t y2); 
    Container* removeContainer(size_t x, size_t y); // remove container from (x,y)
    void rejectContainer(Container* c);
    bool emptyCoordinate(size_t x, size_t y){ return storage.emptyCoordinate(x, y); }
    bool fullCoordinate(size_t x, size_t y){return storage.fullCoordinate(x, y);}
    pair<size_t, size_t> getStorageDimensions(){ return storage.getDimensions(); }
    void setLoggerFile(const string& file_path){logger.setLogFile(file_path);}
    void closeLogFile(){logger.closeLogFile();}
    
};

#endif /* SHIP_H */
