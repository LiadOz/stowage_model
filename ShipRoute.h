#pragma once

#include <vector>
#include "Port.h"
#include <fstream>
#include <string>

using std::vector;
using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;

class ShipRoute {
private:
	vector<Port> route;
public:
	ShipRoute() {};
	ShipRoute(string filePath);

	vector<Port>& getRoute() {
		return route;
	}

};