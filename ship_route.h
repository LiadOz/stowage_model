#ifndef SHIPROUTE_H
#define SHIPROUTE_H

#include <vector>
#include <fstream>
#include <string>

#include "Port.h"

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
	ShipRoute(const string& filePath);

	vector<Port>& getRoute() {
		return route;
	}
};

#endif /* SHIPROUTE_H */
