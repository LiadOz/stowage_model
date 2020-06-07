#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <memory>
#include <filesystem>

namespace fs = std::filesystem;

using std::string;
using std::vector;
using std::ofstream;
using std::stringstream;
using std::shared_ptr;
using fs::path;

//files special chars defs
#define FILE_COMMENT_LINE_CHAR '#'
#define FILE_LINE_SEPARATOR_CHAR ','

//files params
#define PORT_FILE_NUM_OF_PARAMS 3
#define SHIPROUTE_FILE_NUM_OF_PARAMS 1
#define CRANE_OPERATIONS_FILE_MAX_NUM_OF_PARAMS 8

//commandline params
#define COMMAND_LINE_ALGORITHM "-algorithm_path"
#define COMMAND_LINE_TRAVEL "-travel_path"
#define COMMAND_LINE_OUTPUT "-output"
#define COMMAND_LINE_FOLDER_SEPARATOR "/"

//files extensions
#define DYNAMIC_FILE_EXTENSION ".so"

bool validRoute(const string& route);
bool validCargoFile(const string& filename);
bool isCommentLine(const string& line);
// throws exception if got too many arugments
vector<string> getDataFromLine(const string& line, int howManyParams, bool unlimitedParams = false);
stringstream getCommandLineParameters(int argc, char** argv);
bool isDirectoriesExists(const path& algorithmPath,const path& travelPath);
// returns path to file with certian extension
string getFileWithExt(const string& folder, const string& ext);

// making the logger easier to start
#define LOG Logger::Instance()
// singleton to log errors 
// cannot be while the program is runnig
class Logger{
private:
    Logger(){};
    Logger(Logger const&);
    Logger& operator=(Logger const&);
    string logType;
    string filePath;
    bool firstLine = true;
    bool logged = false;
public:
    static Logger& Instance();
    void setFile(const string& file_path){filePath=file_path; firstLine = true;}
    void logError(const string& message);
    void setLogType(const string& type);
    ~Logger();
};
