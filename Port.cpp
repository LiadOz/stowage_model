#include "Port.h"
#include <sstream>
#include <stdexcept>
#include "util.h"

using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;

Port::Port(string code, string filePathForCargo) {
    if(!validRoute(code)){
        throw std::runtime_error("Invalid route");
    }
	seaPortCode = code;
	cargoFilePath = filePathForCargo;
}

bool Port::LoadContainersFromFile(string filePath) {

	ifstream file(filePath);
	string lineFromFile;
	vector<string> containerData;

	//data members for a container
	string containerID;
	int containerWeight;
	string portDest;

	while (getline(file, lineFromFile))
	{

		/*if line is a comment - ignore*/
		if (isCommentLine(lineFromFile))
		{
			continue;
		}

		containerData = getDataFromLine(lineFromFile, PORT_FILE_NUM_OF_PARAMS);

			//try to parse the first param to weight & create the object
        try {
            containerWeight = stoi(containerData[1]);
            containerID = containerData[0];
            portDest = containerData[2];

            Container container(containerWeight, portDest, containerID);

            AddContainer(container);
        }
        catch (std::invalid_argument& error) {
            Logger::Instance().logError(error.what());
        }
	}

	file.close();
	this->cargoFilePath = filePath;

	//TODO: decide if when failing try to keep reading, or return false on first fail
	return true;
}


bool Port::AddContainer(Container containerToAdd) {
	for (Container container : containers) {
		if (container.getId() == containerToAdd.getId())
		{
			return false;
		}
	}

	containers.push_back(containerToAdd);
	return true;
}

bool Port::RemoveContainer(Container containerToRemove) {

	for (size_t index = 0; index < containers.size(); index++)
	{
		if (containers[index].getId() == containerToRemove.getId())
		{
			containers.erase(containers.begin() + index);
			return true;
		}
	}

	return false;
}
