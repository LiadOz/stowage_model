#include "Logger.h"

#include <iostream>

Logger &Logger::Instance() {
    static Logger instance;
    return instance;
}


thread_local string Logger::logType;

void Logger::logError(const string& message) {
    // 2020-06-04 09:52 TODO : not open file every time
    std::lock_guard<std::mutex> lock(locker);
    string error = "Error in " + logType + ": " + message; 
    file << error << std::endl;
    std::cerr << error << std::endl;
    logged = true;
}

void Logger::setFile(const string& file_path){
    file.open(file_path); 
}
void Logger::setLogType(const string& type) {
    logType = type;
}

Logger::~Logger(){
    file.close();
    if (!logged) remove(filePath.c_str());
}
