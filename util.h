#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <ostream>
#include <fstream>

using std::string;
using std::vector;
using std::ofstream;

//files special chars defs
#define FILE_COMMENT_LINE_CHAR '#'
#define FILE_LINE_SEPARATOR_CHAR ','

//files params
#define PORT_FILE_NUM_OF_PARAMS 3
#define SHIPROUTE_FILE_NUM_OF_PARAMS 1
#define CRANE_OPERATIONS_FILE_MAX_NUM_OF_PARAMS 7

//General commons
bool ValidRoute(const string& route);
bool ValidCargoFile(const string& filename);
bool IsCommentLine(const string& line);
// throws exception if got too many arugments
vector<string> GetDataFromLine(const string& line, int howManyParams, bool unlimitedParams = false);

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
    void SetFile(const string& file_path){ file.open(file_path); firstLine = true;}
    void SaveFile(){file.close();}
    void LogError(const string& message);
    void SetLogType(const string& type);
};

#endif /* UTIL_H */
