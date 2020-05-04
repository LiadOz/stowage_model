#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <fstream>
#include <unordered_set>
#include "util.h"
#include "parser.h"
#include "container.h"
#include "algorithm.h"
#include "parser.h"

#define OUTSIDE_X -1
#define OUTSIDE_Y -1
#define PARSING_ID 0
#define PARSING_WEIGHT 1
#define PARSING_PORT 2
#define UNLOAD_ALL "ALL"

using std::regex;
using std::ifstream;
using std::regex_match;
using std::unordered_set;
using std::pair;
using std::ifstream;
using std::stringstream;

int Algorithm::readShipPlan(const string& full_path_and_file_name){
    s = Ship(full_path_and_file_name); 
    //TODO
    return 0;
}

int Algorithm::readShipRoute(const string& full_path_and_file_name){
    routes.clear();
    PARSER(parse, full_path_and_file_name, "Invalid ship rotue file");
    while(parse.Good()){
        vector<string> data;
        parse>>data;
        string line = data[0];
        if(!ValidRoute(line)){
            LOG.LogError("invalid port name " + line);
            continue;
        }
        routes.push_back(line);
    }
    reverse(routes.begin(), routes.end());
    //TODO
    return 0;
}

// unloads all cargo to port and frees current port containers
vector<Container> Algorithm::UnloadAll(string port){
    pair<size_t, size_t> d = s.GetStorageDimensions();
    vector<Container> outside;
    for (size_t i = 0; i < d.second; ++i) {
        for (size_t j = 0; j < d.first; ++j) {
            while(!s.EmptyCoordinate(i, j)){
                Container c = s.RemoveContainer(i, j);
                // freeing the port's cargo
                if (port.compare(UNLOAD_ALL) == 0 || 
                        c.GetDestination().compare(port) == 0);
                else
                    outside.push_back(c);
            }
        }
    }
    return outside;
}

bool Algorithm::InsertNextFree(Container c){
    pair<size_t, size_t> d = s.GetStorageDimensions();
    while(next_x < d.first && next_y < d.second){
        if (!s.FullCoordinate(next_x, next_y)){
            s.InsertContainer(next_x, next_y, c);
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


void SetAwaitingCargo(const string& file_path, vector<Container>& awaiting){
    PARSER(parse, file_path, "Invalid port file");
    while(parse.Good()){
        vector<string> row;
        parse>>row;
        try {
            awaiting.emplace_back(
                    std::stoi(row[PARSING_WEIGHT]),
                    row[PARSING_PORT], row[PARSING_ID]
                    );
        }
        catch(std::invalid_argument& e) { 
                LOG.LogError(e.what());
        }
    }
}

int Algorithm::getInstructionsForCargo(
        const string& input_full_path_and_file_name,
        const string& output_full_path_and_file_name){

    s.SetLoggerFile(output_full_path_and_file_name);

    // when reaching final port
    if(routes.size() == 1)
        UnloadAll(UNLOAD_ALL);
    else {
        string currentPort = routes.back();
        routes.pop_back();
        this->GetPortInstructions(currentPort, input_full_path_and_file_name);
    }
    s.CloseLogFile();
    // TODO
    return 0;
}

int BruteAlgorithm::GetPortInstructions(const string& port,
        const string& input_path){

    vector<Container> outside = UnloadAll(port);
    next_x = next_y = 0;

    // inserting all cargos the were removed
    for (Container c : outside)
        InsertNextFree(c);

    // pushing new cargo
    vector<Container> awaiting;
    SetAwaitingCargo(input_path, awaiting);
    bool success;
    for (auto c : awaiting) {
        success = InsertNextFree(c);
        if (!success){
            s.RejectContainer(c);
        }
            
    }
    /* TODO:  <04-05-20, yourname> */
    return 0;
}

int RejectAlgorithm::GetPortInstructions(const string& port,
        const string& input_path){

    vector<Container> outside = UnloadAll(port);
    next_x = next_y = 0;

    // pushing new cargo
    vector<Container> awaiting;
    SetAwaitingCargo(input_path, awaiting);
    bool success;
    for (auto c : awaiting) {
        if (c.GetDestination().compare(routes.back()) != 0){
            // reject container that is not to the next route
            s.RejectContainer(c);
            continue;
        }
        success = InsertNextFree(c);
        if (!success){
            // reject if there is no more space
            s.RejectContainer(c);
        }
            
    }
    // TODO
    return 0;
}
