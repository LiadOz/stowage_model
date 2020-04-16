#include <iostream>
#include "util.h"

bool valid_file(string file_path){
    return true;
}
int getIthFile(string filename){
    // TODO
    return 0;
}

Logger* Logger::instance_p = nullptr;
Logger& Logger::Instance() {
   if (!instance_p)   // Only allow one instance of class to be generated.
      instance_p = new Logger;
 
   return *instance_p;
}

void Logger::logError(string message){
    std::cout << "Error in " << logType << " : " << message << std::endl;
}
