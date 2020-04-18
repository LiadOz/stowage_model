#include <iostream>
#include <string>
#include <stdlib.h>
#include "container.h"
#include "ship.h"
#include "algorithm.h"
#include "util.h"
#include "Port.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

int main() {
    //Logger& l = Logger::Instance();
    //l.setLogType("creating conatiners");
    //Container* c1 = new Container(10, "a", "CSQU3054383");
    //Container* c2 = new Container(10, "a", "CSQU305438s");
    //string a = "example/sample.plan";
    //Ship s(a);
    //l.setLogType("inserting Containers");
    //s.insertContainer(0, 0, c1);
    //s.insertContainer(0, 0, c2);
    //s.removeContainer(0, 0);
    //s.removeContainer(0, 0);
    //s.removeContainer(0, 0);
    //s.removeContainer(0, 0);
    //s.removeContainer(0, 0);
    //s.removeContainer(0, 0);
    //s.removeContainer(0, 0);

	//Port* p = new Port();
	//cout << p->getPortCode();
	
	Port portA("portA");
	portA.LoadContainersFromFile("./myTests.txt");

	ShipRoute route("./Example/ports");
	return EXIT_SUCCESS;
}
// int main() {
//     Logger& l = Logger::Instance();
//     l.setLogType("init");
//     Algorithm& a = *(new RejectAlgorithm());
//     a.readShipPlan("./example/sample.plan");
//     a.readShipRoute("./example/ports");
//     l.setLogType("alg1");
//     a.getInstructionsForCargo("./example/AERKT_34.cargo_data", "out1");
//     l.setLogType("alg2");
//     a.getInstructionsForCargo("./example/JPSNR_3.cargo_data", "out2");
//     a.getInstructionsForCargo("./example/JPSNR_3.cargo_data", "out3");
// }
