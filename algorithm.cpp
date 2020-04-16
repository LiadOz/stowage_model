#include <regex>
#include <fstream>
#include <unordered_map>
#include "util.h"
#include "algorithm.h"

#define OUTSIDE_X -1
#define OUTSIDE_Y -1

using std::regex;
using std::ifstream;
using std::regex_match;
using std::unordered_map;

void Algorithm::readShipRoute(const string& full_path_and_file_name){
    regex r("[A-Z]{5}");
    vector<string> temp;
    string line;
    ifstream file(full_path_and_file_name);
    while(getline(file, line)){
        if(line[0] == '#') continue;
        if(!regex_match(line, r)){
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
void BruteAlgroithm::getInstructionsForCargo(
        const string& input_full_path_and_file_name,
        const string& output_full_path_and_file_name){
    string currentPort = routes.back();
    //unordered_map something;



    routes.pop_back();
}
