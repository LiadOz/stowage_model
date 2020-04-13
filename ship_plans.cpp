#include "ship_plans.h"

#include <ostream>
using std::ostream;

ostream& operator<<(ostream& out, const Plan& p){
    pair<int, int> dim = p.getDimensions();
    return out << "X = " << dim.first
        << ", Y = " << dim.second;
}

bool ShipPlans::appendPlan(const Plan& plan){
    if(plans.size() == 0){
        plans.push_back(plan);
        return true;
    }

    pair<int, int> dim1 = plan.getDimensions();
    pair<int, int> dim2 = plans[plans.size()-1].getDimensions();
    if (dim1.first >= dim2.first && dim1.second >= dim2.second){
        plans.push_back(plan);
        return true;
    }
    return false;
}

ostream& operator<<(ostream& out, const ShipPlans& p){
    for (int i = 0; i < p.size(); ++i) {
        out << "floor " << i << " " << p.plans[i] << "\n";
    }
    return out;
}
