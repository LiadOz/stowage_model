#include "Port.h"
#include <sstream>
#include <stdexcept>
#include "util.h"
#include <stdexcept>

using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::runtime_error;


Port::Port(const string& code, const string& filePathForCargo) {
    if(!validRoute(code)){
        throw std::runtime_error("Invalid route");
    }
	seaPortCode = code;
	cargoFilePath = filePathForCargo;
}

bool Port::LoadContainersFromFile(const string& filePath) {

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

	return true;
}


bool Port::AddContainer(Container& containerToAdd) {
	for (Container& container : containers) {
		if (container.getId() == containerToAdd.getId())
		{
			return false;
		}
	}

	containers.push_back(containerToAdd);
	return true;
}

Container Port::RemoveContainer(const string& containerToRemove) {

	for (size_t index = 0; index < containers.size(); index++)
	{
		if (containers[index].getId() == containerToRemove)
		{
			Container contToReturn = containers[index];
			containers.erase(containers.begin() + index);
			return contToReturn;
		}
	}

	//TODO: consider changing logic to pointers in exec2
	throw runtime_error("container not in port");
	
}
