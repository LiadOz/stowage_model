#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "inventory.h"
#include "container.h"
#include "ShipRoute.h"

#define INVALID_ARG -1
using std::vector;
using std::string;
using std::pair;
using std::ofstream;

// used to log actions by the ship
class ShipLogger {
private:
    ofstream file;
    bool logToScreen;
public:
    ShipLogger(): logToScreen(false){}
    void setLogFile(const string& file_path){ file.open(file_path);}
    void setLogToScreen(bool flag){ logToScreen = flag;}
    void closeLogFile(){ file.close();}
    void logAction(const string& action);
};

class Ship {
private:
    size_t decks;
    Inventory storage;
    ShipLogger logger;
	int totalCorrectUnloads;
public:
    // when you create a ship you supply the list of plans
    Ship(): totalCorrectUnloads(0){};
    Ship(const string& file_path): storage(file_path), totalCorrectUnloads(0){decks = storage.getNumFloors();}
    // returns the max height of the coordinate
    size_t getCoordinateHeight(size_t x, size_t y){ return storage.getCoordinateHeight(x, y);}
    // pushes container to (x1, y1) throws error if cannot be executed
    void insertContainer(size_t x, size_t y, Container c); // insertes container to (x,y)
    // move container from (x1, y1) to (x2, y2) throws error if cannot be executed
    void moveContainer(size_t x1, size_t y1, size_t x2, size_t y2); 
    // removes container from (x1, y1) throws error if cannot be executed
    Container removeContainer(size_t x, size_t y);
    // used to format rejection to container
    void rejectContainer(Container c);
    bool emptyCoordinate(size_t x, size_t y){ return storage.emptyCoordinate(x, y); }
    bool fullCoordinate(size_t x, size_t y){return storage.fullCoordinate(x, y);}
    pair<size_t, size_t> getStorageDimensions(){ return storage.getDimensions(); }
    void setLoggerFile(const string& file_path){logger.setLogFile(file_path);}
    void setLogToScreen(bool flag){ logger.setLogToScreen(flag);}
    void closeLogFile(){logger.closeLogFile();}
    vector<Container> getShipContainers() {return storage.getAllContainers();}
	void UnloadedCargoAtCorrectPort() { totalCorrectUnloads++; }
	int GetTotalCorrectUnloads() { return totalCorrectUnloads; }
};

#endif /* SHIP_H */
