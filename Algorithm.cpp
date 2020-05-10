#include "Algorithm.h"

#include <stdexcept>
#include <regex>
#include <cmath>

#include "Util.h"
#include "Exceptions.h"
#include "Parser.h"
#include "Container.h"
#include "Parser.h"

using std::regex;
using std::regex_match;
using std::pair;
using std::runtime_error;

#define OUTSIDE_X -1
#define OUTSIDE_Y -1
#define PARSING_ID 0
#define PARSING_WEIGHT 1
#define PARSING_PORT 2
#define UNLOAD_ALL "ALL"

int Algorithm::readShipPlan(const string& full_path_and_file_name){
    int errorStatus = 0;
    try {
        errorStatus = s.readPlan(full_path_and_file_name);
    }catch(Error& e) {
        errorVar(errorStatus, e.getError());
    }
    return errorStatus;
}

int Algorithm::readShipRoute(const string& full_path_and_file_name){
    int errorStatus = 0;
    Parser parse;
    try {
        parse.loadFile(full_path_and_file_name);
    }catch(runtime_error& e) {
        throw FatalError("Bad route file", ERROR_BAD_ROUTE_FILE);
    }

    routes.clear();
    while(parse.good()){
        vector<string> data;
        parse>>data;
        string line = data[0];
        if(!validRoute(line)){
            errorVar(errorStatus, ERROR_BAD_PORT);
            continue;
        }
        if(routes.size() > 0 && line == routes.back()){ // validating no route comes twice back to back
            errorVar(errorStatus, ERROR_DUPLICATE_PORT);
            continue;
        }
        routes.push_back(line);
    }
    if (routes.size() == 1) // checking if only one port exists in file
        errorVar(errorStatus, ERROR_ONE_PORT);
    if (routes.size() == 0) // checking if only one port exists in file
        throw FatalError("Bad route file", ERROR_BAD_ROUTE_FILE);
    reverse(routes.begin(), routes.end());
    return errorStatus;
}

// unloads all cargo to port and frees current port containers
vector<Container> Algorithm::unloadAll(string port){
    pair<size_t, size_t> d = s.getStorageDimensions();
    vector<Container> outside;
    for (size_t i = 0; i < d.second; ++i) {
        for (size_t j = 0; j < d.first; ++j) {
            while(!s.emptyCoordinate(i, j)){
                Container c = s.removeContainer(i, j);
                // freeing the port's cargo
                if (port.compare(UNLOAD_ALL) == 0 || 
                        c.getDestination().compare(port) == 0);
                else
                    outside.push_back(c);
            }
        }
    }
    return outside;
}

bool Algorithm::insertNextFree(Container c){
    pair<size_t, size_t> d = s.getStorageDimensions();
    while(next_x < d.first && next_y < d.second){
        if (!s.fullCoordinate(next_x, next_y)){
            s.insertContainer(next_x, next_y, c);
            return true;
        }
        if (next_x == d.first - 1){
            next_y++;
            next_x = 0;
        }
        else next_x++;
    }
    return false;
}


int setAwaitingCargo(const string& file_path, vector<Container>& awaiting){
    int errorStatus = 0;
    Parser parse;
    try {
        parse.loadFile(file_path);
    }catch(std::runtime_error& e) {

    }
    while(parse.good()){
        vector<string> row;
        parse>>row;
        try {
            awaiting.emplace_back(row);
        }
        catch(NonFatalError& e) { 
            errorVar(errorStatus, e.getError());
        }
    }
    return errorStatus;
}

int Algorithm::getInstructionsForCargo(
        const string& input_full_path_and_file_name,
        const string& output_full_path_and_file_name){

    s.setLoggerFile(output_full_path_and_file_name);

    // when reaching final port
    if(routes.size() == 1)
        unloadAll(UNLOAD_ALL);
    else {
        string currentPort = routes.back();
        routes.pop_back();
        this->getPortInstructions(currentPort, input_full_path_and_file_name);
    }
    s.closeLogFile();
    // TODO
    return 0;
}

int BruteAlgorithm::getPortInstructions(const string& port,
        const string& input_path){

    vector<Container> outside = unloadAll(port);
    next_x = next_y = 0;

    // inserting all cargos the were removed
    for (Container c : outside)
        insertNextFree(c);

    // pushing new cargo
    vector<Container> awaiting;
    setAwaitingCargo(input_path, awaiting);
    bool success;
    for (auto c : awaiting) {
        success = insertNextFree(c);
        if (!success){
            s.rejectContainer(c);
        }
            
    }
    /* TODO:  <04-05-20, yourname> */
    return 0;
}

int RejectAlgorithm::getPortInstructions(const string& port,
        const string& input_path){

    vector<Container> outside = unloadAll(port);
    next_x = next_y = 0;

    // pushing new cargo
    vector<Container> awaiting;
    setAwaitingCargo(input_path, awaiting);
    bool success;
    for (auto c : awaiting) {
        if (c.getDestination().compare(routes.back()) != 0){
            // reject container that is not to the next route
            s.rejectContainer(c);
            continue;
        }
        success = insertNextFree(c);
        if (!success){
            // reject if there is no more space
            s.rejectContainer(c);
        }
            
    }
    // TODO
    return 0;
}

