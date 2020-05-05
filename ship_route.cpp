#include "ship_route.h"

#include "util.h"

ShipRoute::ShipRoute(const string& filePath) {
	ifstream file(filePath);
	string lineFromFile;
	vector<string> portData;

	//data members for a port
	string portName;
	
	while (getline(file, lineFromFile))
	{

		/*if line is a comment - ignore*/
		if (IsCommentLine(lineFromFile))
		{
			continue;
		}

		portData = GetDataFromLine(lineFromFile, SHIPROUTE_FILE_NUM_OF_PARAMS);

        //try to parse the first param to weight & create the object
        try {
            portName = portData[0];
            Port port(portName);
            route.push_back(port);
        }
        catch (std::exception& error) {
            Logger::Instance().LogError(error.what());
        }
	}

	file.close();
}
