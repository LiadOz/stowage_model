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
    file << "," << message;
    std::cerr << "Error in " << logType << ": " << message << std::endl;
    logged = true;
}

void Logger::setFile(const string& file_path){
    firstLine = true;
    file.open(file_path); 
}
void Logger::setLogType(const string& type) {
    if (!firstLine)
        file << std::endl;
    firstLine = false;
    logType = type;
    file << logType;
}

Logger::~Logger(){
    file.close();
    if (!logged) remove(filePath.c_str());
}
