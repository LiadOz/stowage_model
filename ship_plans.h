#ifndef SHIP_PLANS_H
#define SHIP_PLANS_H

#include <vector>
#include <ostream>
using std::vector;
using std::pair;
using std::ostream;

class Plan {
private:
public:
    vector<vector<bool>> plan;
    // creates a new plan with dimesnions x y
    Plan(int x, int y): plan(y, vector<bool>(x, false)){}
    bool isOccupied(int x, int y) const { return plan[x][y]; }
    void setOccupied(int x, int y){ plan[x][y] = true; }
    void setUnoccupied(int x, int y){ plan[x][y] = false; }
    pair<int, int> getDimensions() const { return { plan[0].size(), plan.size()}; }
    //friend ostream& operator<<(ostream& out, const Plan &p);
    //~Plan();
};

class ShipPlans {
private:
    vector<Plan> plans;

public:
    ShipPlans(){};
    // appends a plan if it can be fit on top the previous plan
    bool appendPlan(const Plan& plan);
    int size() const { return plans.size(); }
    friend ostream& operator<<(ostream& out, const ShipPlans &p);
};

#endif /* SHIP_PLANS_H */
