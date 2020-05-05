#include "parser.h"

#include <iostream>
#include <sstream>

using std::stringstream;

Parser::Parser (const string& filePath){
    LoadFile(filePath);
}
void Parser::LoadFile(const string& filePath){
    readFile.open(filePath);
    if(!readFile.good()) throw std::runtime_error("invalid file");
    SkipComments();
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

void Parser::SkipComments(){
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
        data.push_back(word);
    }
    SkipComments();
    return *this;
}
