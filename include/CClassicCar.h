//
// Created by andrei-cristea on 5/26/25.
//

#ifndef CCLASSICCAR_H
#define CCLASSICCAR_H

#include "CCar.h"
#include <string>

class CClassicCar final: public CCar {
    double rarityIndex;
    std::string originCountry;

public:
    CClassicCar(const std::string& b, const std::string& m,
        int y, double r, const std::string& o);

    double basePrice() const override;

    std::string getTypeName() const override;

    CClassicCar(const CClassicCar& other);

    friend std::istream& operator>>(std::istream& is, CClassicCar& c);

    CClassicCar();

    CClassicCar& operator=(const CClassicCar& other);

};



#endif //CCLASSICCAR_H
