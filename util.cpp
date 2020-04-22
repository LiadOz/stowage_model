#include <regex>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "util.h"
#include <sstream>

using std::regex;
using std::regex_match;
using std::runtime_error;
using std::stringstream;

bool validRoute(const string& route){
    regex r("[A-Z]{5}");
    if(!regex_match(route, r))
        return false;
    return true;
}
bool validCargoFile(const string& filename) {
	regex r("[A-Z]{5}_\\d*.cargo_data");
	if (!regex_match(filename, r))
		return false;
	return true;
}

Logger* Logger::instance_p = nullptr;
Logger& Logger::Instance() {
    if (!instance_p){   // Only allow one instance of class to be generated.
        instance_p = new Logger;
    }
    return *instance_p;
}

// currently the logger prints to the screen
void Logger::logError(const string& message){
    file << "," << message;
    //std::cout << "Error in " << logType << " : " << message << std::endl;
}
void Logger::setLogType(const string& type){
    if(!firstLine)
        file << std::endl;
    firstLine = false;
    logType = type; 
    file << logType;
}

bool isCommentLine(const string& line) {

	unsigned index = 0;
	while (index < line.length()) {
		if (isspace(line[index]))
			index++;
		else 
			break;
	}

	/*shouldn't happen - a line full of empty spaces*/
	if (index == line.length())
	{
		/*TODO: maybe better solution?*/
		return true;
	}

	return line[index] == FILE_COMMENT_LINE_CHAR;
}

//get a vector with all data in string format
vector<string> getDataFromLine(const string& line, int howManyParams) {

	vector<string> dataVector;
	stringstream streamLineFromFile(line);
	string data;

	for (int i = 0; i < howManyParams; i++) {
		if (getline(streamLineFromFile, data, FILE_LINE_SEPARATOR_CHAR)) {
			//get rid of whitespace
			stringstream dataStream(data);
			dataStream >> data;

			dataVector.push_back(data);
		}
		else
            throw runtime_error("not enough params");
	}

	//check if there are too many params
    /* TODO: determine if it's needed
	if (getline(streamLineFromFile, data, FILE_LINE_SEPARATOR_CHAR))
        throw runtime_error("too many params");
    */

	return dataVector;
}
