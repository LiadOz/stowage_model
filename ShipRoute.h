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
	vector<Port> const getRoute() {
		return route;
	}

	ShipRoute(string filePath);
};