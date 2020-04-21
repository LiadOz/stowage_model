#include <iostream>
#include <string>
#include <stdlib.h>
#include "container.h"
#include "ship.h"
#include "algorithm.h"
#include "util.h"
#include "Port.h"
#include "simulation.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

int main() {
    //Logger& l = Logger::Instance();
    //l.setLogType("init");
    //Algorithm* b = new RejectAlgorithm();
    //Algorithm& a = *b;
    //a.readShipPlan("./example/sample.plan");
    //a.readShipRoute("./example/ports");
    //l.setLogType("alg1");
    //a.getInstructionsForCargo("./example/AERKT_34.cargo_data", "out1");
    //l.setLogType("alg2");
    //a.getInstructionsForCargo("./example/JPSNR_3.cargo_data", "out2");
    //a.getInstructionsForCargo("./example/JPSNR_3.cargo_data", "out3");
    //delete b;

	//Port* p = new Port();
	//cout << p->getPortCode();
	
	//Port portA("portA");
	//portA.LoadContainersFromFile("./myTests.txt");
	//Port portB("portB");
	//portB.LoadContainersFromFile("./Simulation/travelA/portsCargo/AERKT_34.cargo_data");
	//

	Algorithm* algorithm = new BruteAlgorithm();
	Simulation simulation("example_input_2", algorithm);
	simulation.RunSimulation();
    delete algorithm;

	return EXIT_SUCCESS;
}
