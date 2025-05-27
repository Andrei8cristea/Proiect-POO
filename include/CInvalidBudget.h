//
// Created by andrei-cristea on 5/26/25.
//

#ifndef CINVALIDBUDGET_H
#define CINVALIDBUDGET_H

#include "CException.h"


class CInvalidBudget final: public  CException {
public:
    CInvalidBudget(int budget);
};



#endif //CINVALIDBUDGET_H
