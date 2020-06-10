#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../common/Container.h"

using std::string;
using std::vector;

#define EMPTY_FILE "emptyFile.txt"  //for when there's no file for creating a port

class Port {
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

    const vector<Container>& getCargoList() const {
        return containers;
    }

    Port(const string& code, const string& cargoFilePath = std::filesystem::current_path().string() + '/' + EMPTY_FILE);
    bool loadContainersFromFile(const string& filePath);
    bool addContainer(Container& containerToAdd);
    Container removeContainer(const string& containerToRemove);
    static bool validateSeaPortCode(const string& code);
};

vector<Port> createShipRoute(const string& filePath);
