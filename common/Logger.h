#pragma once

#include <string>
#include <mutex>
#include <fstream>

using std::ofstream;
using std::string;

// making the logger easier to start
#define LOG Logger::Instance()
// singleton to log errors 
// cannot be while the program is runnig
class Logger{
private:
    ofstream file;
    string filePath;
    std::mutex locker;
    bool firstLine = true;
    bool logged = false;

    Logger(){};
    Logger(Logger const&);
    Logger& operator=(Logger const&);
    static thread_local string logType;
public:
    static Logger& Instance();
    void logError(const string& message);
    void setFile(const string& file_path);
    void setLogType(const string& type);
    ~Logger();
};
