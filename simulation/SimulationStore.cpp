#include "SimulationStore.h"

#include <iostream>

#include "../common/Exceptions.h"
#include "Port.h"

vector<Port> SimulationStore::getRouteFromStore(const string& routePath) {

    auto routeIterator = this->routeStore.find(routePath);
    if (routeIterator != this->routeStore.end()) {
        return routeIterator->second;
    }

    //not stored already, read from file and store it
    try {
        auto newRoute = createShipRoute(routePath);
        this->routeStore.insert(std::pair<string, vector<Port>>(routePath, newRoute));
        std::cout << "reading " + routePath + "for first time (?)" << std::endl;
        return newRoute;
    }

    catch (FatalError& ferror) {
        invalidateFiles.insert(routePath);
        throw ferror;
    }
}

Ship SimulationStore::getShipFromStore(const string& shipPlanPath) {

    auto shipIterator = this->shipPlanStore.find(shipPlanPath);
    if (shipIterator != this->shipPlanStore.end()) {
        return shipIterator->second;
    }

    //not stored already, read from file and store it
    try {
        Ship ship;
        ship.readPlan(shipPlanPath);
        vector<Ship> vs;
        std::pair<string, vector<Ship>> pairr;
        this->shipPlanStore.insert(std::pair<string, Ship>(shipPlanPath, ship));
        std::cout << "\t reading " + shipPlanPath + "for first time (?)" << std::endl;
        return ship;
    }

    catch (FatalError& ferror) {
        invalidateFiles.insert(shipPlanPath);
        throw ferror;
    }
}

bool SimulationStore::isValidFile(const string& path) {
    
        auto invalidFileIterator = invalidateFiles.find(path);
        return (invalidFileIterator == invalidateFiles.end());
    
    return true;
}
