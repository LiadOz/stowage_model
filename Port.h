#ifndef PORT_H
#define PORT_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
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


#endif /* PORT_H */
