#ifndef PORT_H
#define PORT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "container.h"

using std::string;
using std::vector;

class Port
{
private:
	string seaPortCode;
	vector<Container> containers;
	string cargoFilePath;

public:
	string getPortCode() {
		return seaPortCode;
	}

	string getCargoFilePath() {
		return cargoFilePath;
	}

	Port(const string& code, const string& cargoFilePath = "");
	bool LoadContainersFromFile(const string& filePath);
	bool AddContainer(Container& containerToAdd);
	Container RemoveContainer(const string& containerToRemove);
	static bool validateSeaPortCode(const string& code);
};

vector<Port> createShipRoute(const string& filePath);

#endif /* PORT_H */
