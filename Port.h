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
	bool validateSeaPortCode(string code);

public:
	string const getPortCode() {
		return seaPortCode;
	}

	Port(string code);
	bool LoadContainersFromFile(string filePath);
	bool AddContainer(Container containerToAdd);
	bool RemoveContainer(Container containerToRemove);
};