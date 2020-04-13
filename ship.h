#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <string>
#include "ship_plans.h"
using std::vector;
using std::string;

class Ship {
private:
    int decks;
    vector<string> routes;
    // each plan can be a matrix of boolean which indicate open spaces
    ShipPlans plans;

public:
    // when you create a ship you supply the list of plans
    Ship();
    virtual ~Ship();
};

#endif /* SHIP_H */
