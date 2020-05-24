#include "Util.h"

#include <stdlib.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>

#include "Exceptions.h"
#define DYNAMIC_FILE_EXTENSION ".so"

#define ERROR_NO_FILE "no files found the ext "
#define ERROR_TOO_MANY_FILES "found too many files with the ext "

namespace fs = std::filesystem;

using std::cerr;
using std::cout;
using std::endl;
using std::regex;
using std::regex_match;
using std::runtime_error;
using std::stringstream;

bool validRoute(const string &route) {
    regex r("[A-Z]{5}");
    if (!regex_match(route, r))
        return false;
    return true;
}
bool validCargoFile(const string &filename) {
    regex r("[A-Z]{5}_\\d*.cargo_data");
    if (!regex_match(filename, r))
        return false;
    return true;
}

Logger &Logger::Instance() {
    static Logger instance;
    return instance;
}

// currently the logger prints to the screen

void Logger::logError(const string &message) {
    ofstream file;
    file.open(filePath, std::ios::out | std::ios::app);
    file << "," << message;
    file.close();
    std::cerr << "Error in " << logType << " : " << message << std::endl;
}
void Logger::setLogType(const string &type) {
    ofstream file;
    file.open(filePath, std::ios::out | std::ios::app);
    if (!firstLine)
        file << std::endl;
    firstLine = false;
    logType = type;
    file << logType;
    file.close();
}

bool isCommentLine(const string &line) {
    unsigned index = 0;
    while (index < line.length()) {
        if (isspace(line[index]))
            index++;
        else
            break;
    }

    /*shouldn't happen - a line full of empty spaces, but ignore line anyways*/
    if (index == line.length()) {
        return true;
    }

    return line[index] == FILE_COMMENT_LINE_CHAR;
}

//get a vector with all data in string format
//NOTE: not enough time for a pretty solution,
//unlimitedParams is to bypass not enough params error (for crane operations where you can get different amount of params),
//should create a new function and delete this logic later
vector<string> getDataFromLine(const string &line, int howManyParams, bool unlimitedParams) {
    vector<string> dataVector;
    stringstream streamLineFromFile(line);
    string data;

    for (int i = 0; i < howManyParams; i++) {
        if (getline(streamLineFromFile, data, FILE_LINE_SEPARATOR_CHAR)) {
            //get rid of whitespace
            stringstream dataStream(data);
            dataStream >> data;

            dataVector.push_back(data);
        } else if (!unlimitedParams)
            throw runtime_error("not enough params");
    }

    //check if there are too many params
    /* TODO: determine if it's needed
	if (getline(streamLineFromFile, data, FILE_LINE_SEPARATOR_CHAR))
		throw runtime_error("too many params");
	*/

    return dataVector;
}

string getCommandLineParameterByName(int argc, char **argv, string paramName) {
    //we don't need to check last param, as nothing will follow afterwards
    for (int i = 0; i < argc - 1; i++) {
        if (argv[i] == paramName) {
            //check if next param is a flag, aka requested param was empty
            if (argv[i + 1][0] == '-') {
                return "";
            }

            //return param, if it starts with dot remove it
            string paramVal = argv[i + 1];
            return paramVal[0] != '.' ? paramVal : paramVal.substr(1);
        }
    }

    return "";
}

void validateAndChangeDirectories(string &algorithmPathStr, string &outputPathStr, string &travelPathStr) {
    string defaultPath = fs::current_path().string();

    path algorithmPath{defaultPath + COMMAND_LINE_FOLDER_SEPARATOR + algorithmPathStr};
    path outputPath{defaultPath + COMMAND_LINE_FOLDER_SEPARATOR + outputPathStr};
    path travelPath{defaultPath + COMMAND_LINE_FOLDER_SEPARATOR + travelPathStr};

    if (!fs::exists(algorithmPath)) {
        //todo: log in err file as well
        cerr << "Provided algorithm directory doesn't exist. using root folder for algorithms instead." << endl;
        algorithmPathStr = defaultPath;
    } else {
        algorithmPathStr = algorithmPath.string();
    }

    if (!fs::exists(travelPath)) {
        throw FatalError("travel path is invalid.");
    } else {
        travelPathStr = travelPath.string();
    }

    try {
        fs::create_directory(outputPath);
        outputPathStr = outputPath.string();
    }

    catch (std::filesystem::filesystem_error &fs_error) {
        //todo: log in err file as well
        cerr << fs_error.what() << endl;
        cerr << "using root folder for output instead." << endl;
        outputPathStr = defaultPath;
    }
}

stringstream getCommandLineParameters(int argc, char **argv) {
    string algorithmPath;
    string travelPath;
    string outputPath;

    travelPath = getCommandLineParameterByName(argc, argv, COMMAND_LINE_TRAVEL);

    //if no travel_path argument passed, throw fatal error
    if (!travelPath.size()) {
        throw FatalError("Missing -travel_path argument");
    }

    algorithmPath = getCommandLineParameterByName(argc, argv, COMMAND_LINE_ALGORITHM);
    outputPath = getCommandLineParameterByName(argc, argv, COMMAND_LINE_OUTPUT);

    //will change all relative paths to full paths
    try {
        validateAndChangeDirectories(algorithmPath, outputPath, travelPath);
    }

    catch (FatalError &ferror) {
        throw ferror;
    }

    stringstream ss("");
    ss << algorithmPath << " " << travelPath << " " << outputPath;

    return ss;
}

string getFileWithExt(const string &folder, const string &ext) {
    int numOfFilesCounter = 0;
    string path;

    for (const auto &entry : fs::directory_iterator(folder))
        if (entry.path().filename().extension() == ext) {
            path = entry.path().string();
            numOfFilesCounter++;
        }

    if (numOfFilesCounter == 0) {
        throw FatalError(string(ERROR_NO_FILE) + ext);
    }

    if (numOfFilesCounter > 1) {
        throw FatalError(string(ERROR_TOO_MANY_FILES) + ext);
    }
    return path;
}
