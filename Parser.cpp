#include "Parser.h"

#include <iostream>
#include <sstream>

using std::stringstream;

Parser::Parser (const string& filePath){
    loadFile(filePath);
}
void Parser::loadFile(const string& filePath){
    readFile.open(filePath);
    if(!readFile.good()) throw std::runtime_error("invalid file");
    skipComments();
}

bool IsComment(const string& line) {

    // ignoring spaces
	unsigned index = 0;
	while (index < line.length()) {
		if (isspace(line[index]))
			index++;
		else 
			break;
	}

	if (index == line.length()) {
		return true;
	}

	return line[index] == FILE_COMMENT_LINE_CHAR;
}

void Parser::skipComments(){
    string line;
    int curr;
    do {
        curr = readFile.tellg();
        if(!getline(readFile, line)){
            moreLines = false;
            return;
        }
    } while (IsComment(line));
    readFile.seekg(curr);

}

Parser& Parser::operator>>(vector<string>& data){
    string line;
    getline(readFile, line);
    stringstream ss(line);
    while(ss.good()){
        string word;
        getline(ss, word, ',');

        // trimming the words
        word.erase(0, word.find_first_not_of(' '));
        word.erase(word.find_last_not_of(' ')+1);

        data.push_back(word);
    }
    skipComments();
    return *this;
}
