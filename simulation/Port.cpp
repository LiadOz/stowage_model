#include "Port.h"

#include <stdexcept>

#include "Util.h"
#include "Parser.h"

using std::runtime_error;

Port::Port(const string& code, const string& filePathForCargo) {
    if(!validRoute(code)){
        throw std::runtime_error("Invalid route");
    }
	seaPortCode = code;
	cargoFilePath = filePathForCargo;
}

bool Port::loadContainersFromFile(const string& filePath) {

    Parser parse;
    try {
        parse.loadFile(filePath);
    }catch(runtime_error& e) {
        throw runtime_error("Invalid port file");
    }

	while (parse.good()) {
        //data members for a container
        string containerID;
        int containerWeight;
        string portDest;

        vector<string> containerData;
		parse>>containerData;
        if (containerData.size() < PORT_FILE_NUM_OF_PARAMS){
            Logger::Instance().logError("cargo missing arguments");
        }

        //try to parse the first param to weight & create the object
        try {
            containerWeight = stoi(containerData[1]);
            containerID = containerData[0];
            portDest = containerData[2];

            Container container(containerWeight, portDest, containerID);

            addContainer(container);
        }
        catch (std::runtime_error& error) {
            Logger::Instance().logError(error.what());
        }
	}

	this->cargoFilePath = filePath;

	return true;
}


bool Port::addContainer(Container& containerToAdd) {
	for (Container& container : containers) {
		if (container.getId() == containerToAdd.getId())
		{
			return false;
		}
	}

	containers.push_back(containerToAdd);
	return true;
}

Container Port::removeContainer(const string& containerToRemove) {

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

vector<Port> createShipRoute(const string& filePath){
    PARSER(parse, filePath, "Invalid route file");
    vector<Port> shipRoute;
    while(parse.good()){
        vector<string> data;
        parse >> data;
        try {
            shipRoute.emplace_back(data[0]);
        }catch(std::exception& e) {
            LOG.logError(e.what()); // the port does not exist so we skip
        }
    }
    return shipRoute;
}
