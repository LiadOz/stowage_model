#pragma once

#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>

#include "../common/Ship.h"
#include "Port.h"

using std::unordered_map;
using std::map;
using std::unordered_set;

class SimulationStore {
   private:

    //caching stores for routes and ship plans
    unordered_map<string, vector<Port>> routeStore;
    map<string, vector<Ship>> shipPlanStore;

   public:
    SimulationStore(){};

    //get route from the store
    vector<Port> getRouteFromStore(const string& routePath);
    
    //get ship from the store
    Ship getShipFromStore(const string& shipPlanPath);
};