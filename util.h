#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

//TODO: move this to a better place
//files special chars defs
#define FILE_COMMENT_LINE_CHAR '#'
#define FILE_LINE_SEPARATOR_CHAR ','

//files params
#define PORT_FILE_NUM_OF_PARAMS 3
#define SHIPROUTE_FILE_NUM_OF_PARAMS 1

using std::string;
using std::vector;

//General commons

int getIthFile(string filename);
bool validRoute(string route);
bool isCommentLine(string line);
vector<string> getDataFromLine(string line, int howManyParams);

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

#endif /* UTIL_H */
