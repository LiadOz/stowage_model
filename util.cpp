#include <regex>
#include <iostream>
#include "util.h"

using std::regex;
using std::regex_match;

bool valid_file(string file_path){
    return true;
}
int getIthFile(string filename){
    // TODO
    return 0;
}
bool validRoute(string route){
    regex r("[A-Z]{5}");
    if(!regex_match(route, r))
        return false;
    return true;
}

Logger* Logger::instance_p = nullptr;
Logger& Logger::Instance() {
   if (!instance_p)   // Only allow one instance of class to be generated.
      instance_p = new Logger;
 
   return *instance_p;
}

// currently the logger prints to the screen
void Logger::logError(string message){
    std::cout << "Error in " << logType << " : " << message << std::endl;
}
