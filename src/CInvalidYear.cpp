//
// Created by andrei-cristea on 5/26/25.
//

#include "CInvalidYear.h"


CInvalidYear::CInvalidYear(const int year)
    :CException("Invalid year " + std::to_string(year) + " is not >= 1886"){}
