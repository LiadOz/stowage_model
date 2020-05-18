#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../common/Container.h"

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
	bool loadContainersFromFile(const string& filePath);
	bool addContainer(Container& containerToAdd);
	Container removeContainer(const string& containerToRemove);
	static bool validateSeaPortCode(const string& code);
};

vector<Port> createShipRoute(const string& filePath);
