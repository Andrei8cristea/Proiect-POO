//
// Created by andrei-cristea on 5/26/25.
//

#include "CInvalidBudget.h"

CInvalidBudget::CInvalidBudget(int const budget)
    :CException("Invalid budget. Budget cannot be  " +std::to_string(budget) +  " \nYour budget must be in between 1 and 999999"){}
