#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <fstream>

using std::string;
using std::vector;
using std::ofstream;
using std::stringstream;

//files special chars defs
#define FILE_COMMENT_LINE_CHAR '#'
#define FILE_LINE_SEPARATOR_CHAR ','

//files params
#define PORT_FILE_NUM_OF_PARAMS 3
#define SHIPROUTE_FILE_NUM_OF_PARAMS 1
#define CRANE_OPERATIONS_FILE_MAX_NUM_OF_PARAMS 7

//commandline params
#define COMMAND_LINE_ALGORITHM "-algorithm_path"
#define COMMAND_LINE_TRAVEL "-travel_path"
#define COMMAND_LINE_OUTPUT "-output"
#define COMMAND_LINE_DEFAULT_FOLDER "/"

bool validRoute(const string& route);
bool validCargoFile(const string& filename);
bool isCommentLine(const string& line);
// throws exception if got too many arugments
vector<string> getDataFromLine(const string& line, int howManyParams, bool unlimitedParams = false);
stringstream getCommandLineParameters(int argc, char** argv);

// making the logger easier to start
#define LOG Logger::Instance()
// singleton to log errors 
// cannot be while the program is runnig
class Logger{
private:
    Logger(){};
    Logger(Logger const&);
    Logger& operator=(Logger const&);
    static Logger* instance_p;
    string logType;
    ofstream file;
    bool firstLine = true;
public:
    static Logger& Instance();
    void setFile(const string& file_path){ file.open(file_path); firstLine = true;}
    void saveFile(){file.close();}
    void logError(const string& message);
    void setLogType(const string& type);
};