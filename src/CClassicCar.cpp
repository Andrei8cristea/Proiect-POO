//
// Created by andrei-cristea on 5/26/25.
//

#include "CClassicCar.h"
#include "CInvalidYear.h"
#include <iostream>

CClassicCar::CClassicCar(const std::string& b, const std::string& m,
        const int y, const double r, const std::string& o)
            : CCar(b,m,y), rarityIndex(r),originCountry(o){}


double CClassicCar::basePrice() const {
    return 10000 + rarityIndex*100;
}

std::string CClassicCar::getTypeName() const {
    return "Classic";
}

CClassicCar::CClassicCar(const CClassicCar &other)
    :CCar(other),rarityIndex(other.rarityIndex),originCountry(other.originCountry){}

std::istream& operator>>(std::istream& is, CClassicCar& c) {

    is >> static_cast<CCar&>(c);

    if (c.getYear() < 1886) {
        throw CInvalidYear(c.getYear());
    }

    std::cout << "Enter rarityIndex: ";
    is >> c.rarityIndex;
    std::cout << "Enter originCountry: ";
    is >> c.originCountry;
    return is;
}

CClassicCar::CClassicCar()
    : rarityIndex(0.0), originCountry("not_known"){}


CClassicCar &CClassicCar::operator=(const CClassicCar &other) {
    CCar::operator=(other);
    rarityIndex = other.rarityIndex;
    originCountry = other.originCountry;
    return *this;
}