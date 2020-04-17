#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <fstream>
#include <unordered_set>
#include "util.h"
#include "container.h"
#include "algorithm.h"

#define OUTSIDE_X -1
#define OUTSIDE_Y -1
#define PARSING_ID 0
#define PARSING_WEIGHT 1
#define PARSING_PORT 2
#define PARSING_WORDS 3
#define UNLOAD_ALL "ALL"

using std::regex;
using std::ifstream;
using std::regex_match;
using std::unordered_set;
using std::pair;
using std::ifstream;
using std::stringstream;

void Algorithm::readShipRoute(const string& full_path_and_file_name){
    vector<string> temp;
    string line;
    ifstream file(full_path_and_file_name);
    while(getline(file, line)){
        if(line[0] == '#') continue;
        if(!validRoute(line)){
            Logger::Instance().logError("invalid port name " + line);
            continue;
        }
        temp.push_back(line);
    }
    while(!temp.empty()){
        routes.push_back(temp.back());
        temp.pop_back();
    }
}

// unloads all cargo to port and frees current port containers
void Algorithm::unloadAll(string port){
    pair<size_t, size_t> d = s.getStorageDimensions();
    for (size_t i = 0; i < d.second; ++i) {
        for (size_t j = 0; j < d.first; ++j) {
            while(!s.emptyCoordinate(i, j)){
                Container* c = s.removeContainer(i, j);
                // freeing the port's cargo
                if (port.compare(UNLOAD_ALL) == 0 || 
                        c->getDestination().compare(port) == 0)
                    delete c;
                else
                    outside.insert(c);
            }
        }
    }
}

void setAwaitingCargo(const string& file_path, vector<Container*>& awaiting){
    ifstream file(file_path);
    string line, data;

    while(getline(file, line)){
        if(line[0] == '#') continue;
        vector<string> row;
        stringstream s(line);

        for (int i = 0; i < PARSING_WORDS; ++i) {
            getline(s, data, ',');
            row.push_back(data);
        }
        
        Container* c;
        try {
            c = new Container(std::stoi(row[PARSING_WEIGHT]), row[PARSING_PORT], row[PARSING_ID]);
            awaiting.push_back(c);
        }
        catch(std::invalid_argument& e) { 
                Logger::Instance().logError(e.what());
        }
    }
}

void BruteAlgroithm::getInstructionsForCargo(
        const string& input_full_path_and_file_name,
        const string& output_full_path_and_file_name){
    s.setLoggerFile(output_full_path_and_file_name);

    string currentPort = routes.back();
    if(routes.size() == 1)
        currentPort = UNLOAD_ALL;
    
    unloadAll(currentPort);
    next_x = next_y = 0;

    // inserting all cargos the were removed
    for (Container* c : outside)
        insertNextFree(c);

    // pushing new cargo
    vector<Container*> awaiting;
    setAwaitingCargo(input_full_path_and_file_name, awaiting);
    bool success;
    for (auto c : awaiting) {
        success = insertNextFree(c);
        if (!success){
            s.rejectContainer(c);
            delete c;
        }
            
    }
    s.closeLogFile();
    routes.pop_back();
}

bool BruteAlgroithm::insertNextFree(Container* c){
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

