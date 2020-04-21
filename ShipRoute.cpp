#include "ShipRoute.h"
#include "Parser.h"

ShipRoute::ShipRoute(string filePath) {
	ifstream file(filePath);
	string lineFromFile;
	vector<string> portData;

	//data members for a port
	string portName;
	
	while (getline(file, lineFromFile))
	{

		/*if line is a comment - ignore*/
		if (Parser::isCommentLine(lineFromFile))
		{
			continue;
		}

		portData = Parser::getDataFromLine(lineFromFile, SHIPROUTE_FILE_NUM_OF_PARAMS);

		if (portData.size() != SHIPROUTE_FILE_NUM_OF_PARAMS)
		{
			//TODO: error message and stuff
		}

		else
		{
			//try to parse the first param to weight & create the object
			//TODO: validate params when creating a container
			try
			{
				portName = portData[0];
				if (Port::validateSeaPortCode(portName))
				{
					Port port(portName);
					route.push_back(port);
				}
				else
				{
					//TODO: throw an error that port is not valid and log it
				}

			}
			catch (std::invalid_argument& error)
			{
				//TODO: add error to log
				cout << "error in ShipRoute constructor";
			}
		}
	}

	file.close();
}
