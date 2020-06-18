#include "../interfaces/WeightBalanceCalculator.h"

#define NO(x) (void)x;

int WeightBalanceCalculator::readShipPlan(const std::string& full_path_and_file_name){
    return 0;
    NO(full_path_and_file_name);
}

WeightBalanceCalculator::BalanceStatus WeightBalanceCalculator::tryOperation(char loadUnload, int kg, int X, int Y){
    return APPROVED;
    NO(loadUnload)NO(kg)NO(X)NO(Y)NO("OH MAMA MIA") // MAMA MIA LET ME GO
}
