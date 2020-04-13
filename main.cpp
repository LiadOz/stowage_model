#include <iostream>
#include "container.h"
#include "ship_plans.h"

using std::string;
using std::vector;

int main() {
    Container c = {20, "this", "that"};
    ShipPlans s;
    Plan p1(5,5);
    Plan p2(5,5);
    Plan p3(4,5);
    Plan p4(6,5);
    s.appendPlan(p1);
    s.appendPlan(p2);
    s.appendPlan(p3);
    s.appendPlan(p4);
    std::cout << s << std::endl;
    
}
