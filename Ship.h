#pragma once 

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

#include "Inventory.h"
#include "Container.h"

using std::vector;
using std::string;
using std::pair;
using std::ofstream;
using std::unordered_set;

#define INVALID_ARG -1

// used to log actions by the ship
// this is how the algorithm sends actions for the simulations
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

// the ship holds an Inventory variable that holds all the contianers
// it then uses this storage to simulate ship opeartion
class Ship {
private:
    size_t decks;
    Inventory storage;
    ShipLogger logger;
	int totalCorrectUnloads = 0;
    unordered_set<string> idList;
public:
    // when you create a ship you supply the list of plans
    Ship() {};
    int readPlan(const string& file_path);
    size_t getNumFloors(){ return decks;}
    // returns the depth of the coordinate
    size_t getCoordinateDepth(size_t x, size_t y){ return storage.getCoordinateDepth(x, y);}
    size_t getCoordinateHeight(size_t x, size_t y){ return storage.getCoordinateHeight(x, y);}
    bool idOnShip(string id){ return idList.find(id) != idList.end();}
    // pushes container to (x1, y1) throws error if cannot be executed
    void insertContainer(size_t x, size_t y, Container& c); // insertes container to (x,y)
    // move container from (x1, y1) to (x2, y2) throws error if cannot be executed
    void moveContainer(size_t x1, size_t y1, size_t x2, size_t y2); 
    // removes container from (x1, y1) throws error if cannot be executed
    Container removeContainer(size_t x, size_t y);
    // used to format rejection to container
    void rejectContainer(Container& c);

    // used to get information about the ship's state
    bool emptyCoordinate(size_t x, size_t y){ return storage.emptyCoordinate(x, y); }
    bool fullCoordinate(size_t x, size_t y){return storage.fullCoordinate(x, y);}
    pair<size_t, size_t> getStorageDimensions(){ return storage.getDimensions(); }
    vector<Container> getShipContainers() {return storage.getAllContainers();}

    void setLoggerFile(const string& file_path){logger.setLogFile(file_path);}
    void setLogToScreen(bool flag){ logger.setLogToScreen(flag);}
    void closeLogFile(){logger.closeLogFile();}

	void unloadedCargoAtCorrectPort() { totalCorrectUnloads++; }
	int getTotalCorrectUnloads() { return totalCorrectUnloads; }
};
