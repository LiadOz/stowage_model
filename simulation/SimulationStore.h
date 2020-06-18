#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "../common/Ship.h"
#include "Port.h"

using std::unordered_map;
using std::unordered_set;

class SimulationStore {
   private:
    unordered_map<string, vector<Port>> routeStore;
    unordered_map<string, Ship> shipPlanStore;

   public:
    SimulationStore(){};
    vector<Port> getRouteFromStore(const string& routePath);
    Ship getShipFromStore(const string& routePath);
};