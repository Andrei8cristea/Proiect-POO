//
// Created by andrei-cristea on 5/26/25.
//

#ifndef CRALLYCAR_H
#define CRALLYCAR_H

#include "CCar.h"
#include <iostream>
#include <string>


class CRallyCar final: public CCar {
    double rearTractionRatio;
    bool turbocharged;

public:
    CRallyCar(const std::string& b, const std::string& m,
        int y, double r, bool t);

    double basePrice() const override;

    std::string getTypeName() const override;

    CRallyCar(const CRallyCar& other);

    friend std::istream& operator>>(std::istream& is, CRallyCar& c);

    CRallyCar();

    bool isTurbocharged() const;

};



#endif //CRALLYCAR_H
