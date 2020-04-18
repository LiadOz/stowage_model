#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "util.h"
#include <sstream>

using std::string;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;

class Parser 
{
private:
public:
	static bool isCommentLine(string line);
	static vector<string> getDataFromLine(string line, int howManyParams);
};