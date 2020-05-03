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
// this is how the algorithm sends actions for the simulations
class ShipLogger {
private:
    ofstream file;
    bool logToScreen;
public:
    ShipLogger(): logToScreen(false){}
    void SetLogFile(const string& file_path){ file.open(file_path);}
    void SetLogToScreen(bool flag){ logToScreen = flag;}
    void CloseLogFile(){ file.close();}
    void LogAction(const string& action);
};

// the ship holds an Inventory variable that holds all the contianers
// it then uses this storage to simulate ship opeartion
class Ship {
private:
    size_t decks;
    Inventory storage;
    ShipLogger logger;
	int totalCorrectUnloads;
public:
    // when you create a ship you supply the list of plans
    Ship(): totalCorrectUnloads(0){};
    Ship(const string& file_path): storage(file_path), totalCorrectUnloads(0){decks = storage.GetNumFloors();}
    // returns the max height of the coordinate
    size_t GetCoordinateHeight(size_t x, size_t y){ return storage.GetCoordinateHeight(x, y);}
    // pushes container to (x1, y1) throws error if cannot be executed
    void InsertContainer(size_t x, size_t y, Container& c); // insertes container to (x,y)
    // move container from (x1, y1) to (x2, y2) throws error if cannot be executed
    void MoveContainer(size_t x1, size_t y1, size_t x2, size_t y2); 
    // removes container from (x1, y1) throws error if cannot be executed
    Container RemoveContainer(size_t x, size_t y);
    // used to format rejection to container
    void RejectContainer(Container& c);

    // used to get information about the ship's state
    bool EmptyCoordinate(size_t x, size_t y){ return storage.EmptyCoordinate(x, y); }
    bool FullCoordinate(size_t x, size_t y){return storage.FullCoordinate(x, y);}
    pair<size_t, size_t> GetStorageDimensions(){ return storage.GetDimensions(); }
    vector<Container> GetShipContainers() {return storage.GetAllContainers();}

    void SetLoggerFile(const string& file_path){logger.SetLogFile(file_path);}
    void SetLogToScreen(bool flag){ logger.SetLogToScreen(flag);}
    void CloseLogFile(){logger.CloseLogFile();}

	void UnloadedCargoAtCorrectPort() { totalCorrectUnloads++; }
	int GetTotalCorrectUnloads() { return totalCorrectUnloads; }
};

#endif /* SHIP_H */
