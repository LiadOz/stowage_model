#pragma once

#include "Port.h"
#include <sstream>
#include "util.h"

using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;

Port::Port(string code) {
	/*TODO: throw execption if not valid code*/
	seaPortCode = code;
}

bool Port::validateSeaPortCode(string code) {
	/*TODO: REGEX CHECK*/
	return true;
}

bool isCommentLine(string line) {

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
vector<string> getDataFromLine(string line, int howManyParams) {

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

bool Port::LoadContainersFromFile(string filePath) {

	ifstream file(filePath);
	string lineFromFile;
	vector<string> containerData;

	//data members for a container
	string containerID;
	int containerWeight;
	string portDest;


	while (getline(file, lineFromFile))
	{

		/*if line is a comment - ignore*/
		if (isCommentLine(lineFromFile))
		{
			continue;
		}

		containerData = getDataFromLine(lineFromFile, PORT_FILE_NUM_OF_PARAMS);

		if (containerData.size() != PORT_FILE_NUM_OF_PARAMS)
		{
			//TODO: error message and stuff
		}

		else {

			//try to parse the first param to weight & create the object
			//TODO: validate params when creating a container
			try
			{
				containerWeight = stoi(containerData[1]);
				containerID = containerData[0];
				portDest = containerData[2];

				Container container(containerWeight, portDest, containerID);

				AddContainer(container);
			}
			catch (std::invalid_argument)
			{
				//TODO: add error to log
				cout << "can't parse " << containerData[1] << " into an Integer." << endl;
			}
		}
	}

	file.close();

	//TODO: decide if when failing try to keep reading, or return false on first fail
	return true;
};


bool Port::AddContainer(Container containerToAdd) {
	for (Container container : containers) {
		if (container.getId() == containerToAdd.getId())
		{
			return false;
		}
	}

	containers.push_back(containerToAdd);
	return true;
}

bool Port::RemoveContainer(Container containerToRemove) {

	for (size_t index = 0; index < containers.size(); index++)
	{
		if (containers[index].getId() == containerToRemove.getId())
		{
			containers.erase(containers.begin() + index);
			return true;
		}
	}

	return false;
}