#include "Algorithm.h"

#include <stdexcept>
#include <regex>
#include <cmath>
#include <unordered_set>

#include "../common/Util.h"
#include "../common/Exceptions.h"
#include "../common/Parser.h"
#include "../common/Container.h"
#include "../common/Parser.h"

using std::max;
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

// TODO: add error number 18 !!!!!!!!!!!!!!!!!!!!!!!!!!

int Algorithm::readShipPlan(const string& full_path_and_file_name){
    errorStatus = 0;
    try {
        errorStatus = s.readPlan(full_path_and_file_name);
    }catch(Error& e) {
        errorVar(errorStatus, e.getError());
    }
    return errorStatus;
}

int Algorithm::readShipRoute(const string& full_path_and_file_name){
    errorStatus = 0;
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
    if (routes.size() == 0) // checking if no port exists in file
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

Algorithm::InsertStatus Algorithm::insertNextFree(Container& c){
    pair<size_t, size_t> d = s.getStorageDimensions();
    while(next_x < d.first && next_y < d.second){
        if (!s.fullCoordinate(next_x, next_y)){
            s.insertContainer(next_x, next_y, c);
            return SUCCSESS;
        }
        if (next_x == d.first - 1){
            next_y++;
            next_x = 0;
        }
        else next_x++;
    }
    return FULL;
}
Algorithm::InsertStatus Algorithm::insertBiggestDepth(Container& c){
    auto d = s.getStorageDimensions();
    int maxDepth = 0;
    if (s.freeSpaces() == 0)
        return FULL;

    for (size_t i = 0; i < d.first; ++i)
        for (size_t j = 0; j < d.second; ++j)
            maxDepth = max(maxDepth, (int)s.getCoordinateDepth(i, j));

    for (size_t i = 0; i < d.first; ++i)
        for (size_t j = 0; j < d.second; ++j)
            if (s.getCoordinateDepth(i, j) == maxDepth && 
                    calc.tryOperation((char)Action::LOAD, c.getWeight(), i, j)
                    == WeightBalanceCalculator::APPROVED){
                s.insertContainer(i, j, c);
                return SUCCSESS;
            }
    return IMPOSSIBLE;
}

bool Algorithm::validDestination(const string& destination){
    for (auto& x : routes)
        if (x == destination)
            return true;
    return false;
}

void Algorithm::setAwaitingCargo(const string& file_path, vector<Container>& awaiting){
    std::unordered_set<string> cargoIds;

    Parser parse;
    try {
        parse.loadFile(file_path);
    }catch(std::runtime_error& e) {
        errorVar(errorStatus, ERROR_BAD_CARGO_FILE);
    }
    while(parse.good()){
        vector<string> row;
        parse>>row;
        try {
            Container c(row);
            if (!validDestination(c.getDestination()))
                throw NonFatalError("Id " + c.getId() + " route is invalid", ERROR_BAD_CARGO_PORT); 
            if(cargoIds.find(c.getId()) != cargoIds.end())
                throw NonFatalError("Id " + c.getId() + " already at port", ERROR_DUPLICATE_PORT_ID); 
            if (s.idOnShip(c.getId())){
                throw NonFatalError("Id " + c.getId() + " already on ship", ERROR_ID_ON_SHIP); 
        }
            awaiting.push_back(c);
            cargoIds.insert(c.getId());
        }
        catch(NonFatalError& e) { 
            errorVar(errorStatus, e.getError());
        }
    }
}

int Algorithm::getInstructionsForCargo(
        const string& input_full_path_and_file_name,
        const string& output_full_path_and_file_name){

    errorStatus = 0;
    s.setLoggerFile(output_full_path_and_file_name);

    // when reaching final port
    if(routes.size() == 1){
        vector<Container> awaiting;
        if (awaiting.size())
            errorVar(errorStatus, ERROR_BAD_LAST_PORT);
        unloadAll(UNLOAD_ALL);
    }
    else {
        string currentPort = routes.back();
        routes.pop_back();
        vector<Container> awaiting;
        setAwaitingCargo(input_full_path_and_file_name, awaiting);
        this->getPortInstructions(currentPort, awaiting);
    }
    s.closeLogFile();
    return errorStatus;
}

void RejectAlgorithm::getPortInstructions(const string& port,
        vector<Container>& awaiting){

    vector<Container> outside = unloadAll(port);
    next_x = next_y = 0;

    // pushing new cargo
    for (auto c : awaiting) {
        if (c.getDestination().compare(routes.back()) != 0){
            // reject container that is not to the next route
            s.rejectContainer(c);
            continue;
        }
        InsertStatus stat = insertNextFree(c);
        if (stat == FULL){
            // reject if there is no more space
            s.rejectContainer(c);
        }
            
    }
}
