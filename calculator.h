#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "inventory.h"

#define NO(a) (void)(a)

enum BalanceStatus{APPROVED, X_IMBALANCED, Y_IMBALANCED, X_Y_IMBALANCED};
class WeightBalanceCalculator {
private:
    Inventory storage;
public:
    WeightBalanceCalculator ();
    void readShipPlan(const std::string& full_path_and_file_name){ storage = Inventory(full_path_and_file_name);}
    BalanceStatus tryOperation(char loadUnload, int kg, int x, int y){ NO(loadUnload); NO(kg); NO(x); NO(y);return APPROVED;}
};

#endif /* CALCULATOR_H */
