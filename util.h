#ifndef UTIL_H
#define UTIL_H

#include <string>

using std::string;

bool valid_file(string file_path);
int getIthFile(string filename);

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
