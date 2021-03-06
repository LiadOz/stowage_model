// WeightBalanceCalculator.h

#pragma once

#include <string>

class WeightBalanceCalculator {
public:

enum BalanceStatus { 
APPROVED, X_IMBALANCED, Y_IMBALANCED, X_Y_IMBALANCED 
};

// but you may implement it just as: return 0;
int readShipPlan(const std::string& full_path_and_file_name);

BalanceStatus tryOperation(char loadUnload, int kg, int x, int y);
};

