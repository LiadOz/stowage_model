#pragma once

#include <string>

//TODO: move this to a better place
//files special chars defs
#define FILE_COMMENT_LINE_CHAR '#'
#define FILE_LINE_SEPARATOR_CHAR ','

//files params
#define PORT_FILE_NUM_OF_PARAMS 3

using std::string;

//General commons


bool valid_file(string file_path);
int getIthFile(string filename);
bool validRoute(string route);

class Logger{
private:
    Logger(){};
    Logger(Logger const&);
    Logger& operator=(Logger const&);
    static Logger* instance_p;
    string logType;
public:
    static Logger& Instance();
    ~Logger(){delete instance_p;}
    void logError(string message);
    void setLogType(string type){ logType = type; }
};