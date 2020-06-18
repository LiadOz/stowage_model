#include "SimulationStore.h"
#include "Port.h"

vector<Port> SimulationStore::getRouteFromStore(const string& routePath) {
    auto routeIterator = this->routeStore.find(routePath);
    if (routeIterator != this->routeStore.end()) {
        return routeIterator->second;
    }

    //not stored already, read from file and store it
    else {
        auto newRoute = createShipRoute(routePath);
        this->routeStore.insert(std::pair<string, vector<Port>>(routePath, newRoute));
        return newRoute;
    }
}

// Ship SimulationStore::getShipFromStore(const string& shipPlanPath) {
//     auto shipIterator = this->shipPlanStore.find(shipPlanPath);
//     if (shipIterator != this->shipPlanStore.end()) {
//         return shipIterator->second;
//     }

//     //not stored already, read from file and store it
//     else {
//         Ship ship;
//         ship.readPlan(shipPlanPath);
//         vector<Ship> vs;
//         std::pair<string, vector<Ship>> pairr;
//         this->shipPlanStore.insert(std::pair<string, Ship>(shipPlanPath, ship));
//         return ship;
//     }

//     unordered_map<string, Ship> asdf;
// }