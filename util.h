#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <ostream>
#include <fstream>

//files special chars defs
#define FILE_COMMENT_LINE_CHAR '#'
#define FILE_LINE_SEPARATOR_CHAR ','

//files params
#define PORT_FILE_NUM_OF_PARAMS 3
#define SHIPROUTE_FILE_NUM_OF_PARAMS 1
#define CRANE_OPERATIONS_FILE_MAX_NUM_OF_PARAMS 7

using std::string;
using std::vector;
using std::ofstream;

//General commons

int getIthFile(const string& filename);
bool validRoute(const string& route);
bool validCargoFile(const string& filename);
bool isCommentLine(const string& line);
// throws exception if got too many arugments
vector<string> getDataFromLine(string line, int howManyParams, bool unlimitedParams = false);

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
    void setFile(const string& file_path){ file.open(file_path);}
    void saveFile(){file.close();}
    void logError(const string& message);
    void setLogType(const string& type);
};

#endif /* UTIL_H */
