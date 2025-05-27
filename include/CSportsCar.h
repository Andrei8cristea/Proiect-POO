//
// Created by andrei-cristea on 5/26/25.
//

#ifndef CSPORTSCAR_H
#define CSPORTSCAR_H

#include "CCar.h"
#include <iostream>
#include <string>


class CSportsCar final : public CCar {
    int horsePower;
    int topSpeed;

public:
    CSportsCar(const std::string& b, const std::string& m,
        int y, int h, int t);

    double basePrice() const override;

    std::string getTypeName() const override;

    CSportsCar(const CSportsCar& other);

    friend std::istream& operator>>(std::istream& is, CSportsCar& c);

    CSportsCar();

};



#endif //CSPORTSCAR_H
