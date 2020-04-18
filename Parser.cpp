#include "Parser.h"

bool Parser::isCommentLine(string line) {

	unsigned index = 0;
	while (index < line.length()) {
		if (isspace(line[index]))
		{
			index++;
		}
		else {
			break;
		}
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
vector<string> Parser::getDataFromLine(string line, int howManyParams) {

	vector<string> dataVector;
	stringstream streamLineFromFile(line);
	string data;

	for (size_t i = 0; i < howManyParams; i++)
	{
		if (getline(streamLineFromFile, data, FILE_LINE_SEPARATOR_CHAR))
		{
			//get rid of whitespace
			stringstream dataStream(data);
			dataStream >> data;

			dataVector.push_back(data);
		}
		else
		{
			//TODO: add to log
			cout << "error in getDataFromLine, not enough params" << endl;
		};
	}

	//check if there are too many params
	if (getline(streamLineFromFile, data, FILE_LINE_SEPARATOR_CHAR))
	{
		//TODO: add to log
		cout << "error in port load containers, too many params" << endl;
	}

	return dataVector;
}
