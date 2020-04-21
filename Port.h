#pragma once

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

	Port(string code, string cargoFilePath = "");
	bool LoadContainersFromFile(string filePath);
	bool AddContainer(Container containerToAdd);
	bool RemoveContainer(Container containerToRemove);
	static bool validateSeaPortCode(string code);
};