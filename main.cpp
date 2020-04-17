#include "algorithm.h"
#include "util.h"

int main() {
    Logger& l = Logger::Instance();
    l.setLogType("init");
    Algorithm a = BruteAlgroithm();
    a.readShipPlan("./example/sample.plan");
    a.readShipRoute("./example/ports");
    l.setLogType("alg1");
    a.getInstructionsForCargo("./example/AERKT_34.cargo_data", "out1");
    l.setLogType("alg2");
    a.getInstructionsForCargo("./example/JPSNR_3.cargo_data", "out2");
}
