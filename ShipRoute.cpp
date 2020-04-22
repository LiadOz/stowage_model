#include "ShipRoute.h"
#include "util.h"

ShipRoute::ShipRoute(string filePath) {
	ifstream file(filePath);
	string lineFromFile;
	vector<string> portData;

	//data members for a port
	string portName;
	
	while (getline(file, lineFromFile))
	{

		/*if line is a comment - ignore*/
		if (isCommentLine(lineFromFile))
		{
			continue;
		}

		portData = getDataFromLine(lineFromFile, SHIPROUTE_FILE_NUM_OF_PARAMS);

        //try to parse the first param to weight & create the object
        try {
            portName = portData[0];
            Port port(portName);
            route.push_back(port);
        }
        catch (std::exception& error) {
            Logger::Instance().logError(error.what());
        }
	}

	file.close();
}
