#include "Port.h"

#include <stdexcept>

#include "../common/Exceptions.h"
#include "../common/Parser.h"
#include "../common/Util.h"

using std::runtime_error;

Port::Port(const string &code, const string &filePathForCargo) {
    if (!validRoute(code)) {
        throw std::runtime_error("Invalid route");
    }
    seaPortCode = code;
    cargoFilePath = filePathForCargo;
}

bool Port::loadContainersFromFile(const string &filePath) {
    Parser parse;
    try {
        parse.loadFile(filePath);
    } catch (runtime_error &e) {
        throw runtime_error("Invalid port file");
    }

    while (parse.good()) {
        // data members for a container
        string containerID;
        int containerWeight;
        string portDest;

        vector<string> containerData;
        parse >> containerData;
        if (containerData.size() < PORT_FILE_NUM_OF_PARAMS) {
            Logger::Instance().logError("cargo missing arguments");
        }

        // try to parse the first param to weight & create the object
        try {
            containerWeight = stoi(containerData[1]);
            containerID = containerData[0];
            portDest = containerData[2];

            Container container(containerWeight, portDest, containerID);

            addContainer(container);
        } catch (std::runtime_error &error) {
            Logger::Instance().logError(error.what());
        }
    }

    this->cargoFilePath = filePath;

    return true;
}

bool Port::addContainer(Container &containerToAdd) {
    for (Container &container : containers) {
        if (container.getId() == containerToAdd.getId()) {
            return false;
        }
    }

    containers.push_back(containerToAdd);
    return true;
}

Container Port::removeContainer(const string &containerToRemove) {
    for (size_t index = 0; index < containers.size(); index++) {
        if (containers[index].getId() == containerToRemove) {
            Container contToReturn = containers[index];
            containers.erase(containers.begin() + index);
            return contToReturn;
        }
    }

    // TODO: consider changing logic to pointers in exec2
    throw runtime_error("container not in port");
}

vector<Port> createShipRoute(const string &filePath) {
    PARSER(parse, filePath, ERROR_STRING_BAD_ROUTE_FILE);
    vector<Port> shipRoute;
    string previousPort = "";
    bool isFirstTime = true;

    while (parse.good()) {
        vector<string> data;
        parse >> data;
        string port = data[0];
        // check if port is repeated twice or more in a row
        if (isFirstTime) {
            isFirstTime = false;
            previousPort = data[0];
        }

        else {
            if (port == previousPort) {
                LOG.logError(string(ERROR_STRING_DUPLICATE_PORT) + "[" + port + "]");
            }
            previousPort = port;
        }

        try {
            shipRoute.emplace_back(data[0]);
        } catch (std::exception &e) {
            // the port does not exist so we skip
            LOG.logError(string(ERROR_STRING_BAD_PORT) + "[" + port + "]");
        }
    }

    // only having 1 port is not legal
    if (shipRoute.size() == 1) {
        LOG.logError(ERROR_STRING_ONE_PORT);
        shipRoute.pop_back();
    }

    return shipRoute;
}
