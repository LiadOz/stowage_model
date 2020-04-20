#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "inventory.h"

enum BalanceStatus{APPROVED, X_IMBALANCED, Y_IMBALANCED, X_Y_IMBALANCED};
class WeightBalanceCalculator {
private:
    Inventory storage;
public:
    WeightBalanceCalculator ();
    void readShipPlan(const std::string& full_path_and_file_name){ storage = Inventory(full_path_and_file_name);}
    BalanceStatus tryOperation(char loadUnload, int kg, int x, int y){ return APPROVED;}
};

#endif /* CALCULATOR_H */
