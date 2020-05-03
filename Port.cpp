#include "Port.h"
#include <sstream>
#include <stdexcept>
#include "util.h"
#include <stdexcept>
#include "parser.h"

using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::runtime_error;


Port::Port(const string& code, const string& filePathForCargo) {
    if(!ValidRoute(code)){
        throw std::runtime_error("Invalid route");
    }
	seaPortCode = code;
	cargoFilePath = filePathForCargo;
}

bool Port::LoadContainersFromFile(const string& filePath) {

    Parser parse;
    try {
        parse.LoadFile(filePath);
    }catch(runtime_error& e) {
        throw runtime_error("Invalid port file");
    }

	while (parse.Good()) {
        //data members for a container
        string containerID;
        int containerWeight;
        string portDest;

        vector<string> containerData;
		parse>>containerData;
        if (containerData.size() < PORT_FILE_NUM_OF_PARAMS){
            Logger::Instance().LogError("cargo missing arguments");
        }

        //try to parse the first param to weight & create the object
        try {
            containerWeight = stoi(containerData[1]);
            containerID = containerData[0];
            portDest = containerData[2];

            Container container(containerWeight, portDest, containerID);

            AddContainer(container);
        }
        catch (std::invalid_argument& error) {
            Logger::Instance().LogError(error.what());
        }
	}

	this->cargoFilePath = filePath;

	return true;
}


bool Port::AddContainer(Container& containerToAdd) {
	for (Container& container : containers) {
		if (container.GetId() == containerToAdd.GetId())
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
		if (containers[index].GetId() == containerToRemove)
		{
			Container contToReturn = containers[index];
			containers.erase(containers.begin() + index);
			return contToReturn;
		}
	}

	//TODO: consider changing logic to pointers in exec2
	throw runtime_error("container not in port");
	
}
