//
// Created by andrei-cristea on 5/26/25.
//

#ifndef CINVALIDYEAR_H
#define CINVALIDYEAR_H

#include "CException.h"

class CInvalidYear final : public CException {
public:
    explicit CInvalidYear(int year);
};



#endif //CINVALIDYEAR_H
