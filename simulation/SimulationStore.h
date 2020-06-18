#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <list>

#include "../common/Ship.h"
#include "Port.h"

using std::unordered_map;
using std::map;
using std::list;

class SimulationStore {
   private:

    //caching stores for routes and ship plans
    unordered_map<string, vector<Port>> routeStore;
    unordered_map<string, Ship> shipPlanStore;
    unordered_set<string> invalidateFiles;

    //used to not re-read invalidated files 
    bool isValidFile(const string& path);
    
   public:
    SimulationStore(){};

    //get route from the store
    vector<Port> getRouteFromStore(const string& routePath);
    
    //get ship from the store
    Ship getShipFromStore(const string& shipPlanPath);

};
