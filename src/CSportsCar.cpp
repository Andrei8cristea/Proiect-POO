//
// Created by andrei-cristea on 5/26/25.
//

#include "CSportsCar.h"
#include "CInvalidYear.h"

CSportsCar::CSportsCar(const std::string &b, const std::string &m,const int y,const int h,const int t)
    :CCar(b,m,y),horsePower(h),topSpeed(t){}


double CSportsCar::basePrice() const {
    return 10000 + horsePower*100;
}

std::string CSportsCar::getTypeName() const {
    return "Sports";
}

CSportsCar::CSportsCar(const CSportsCar &other)
    :CCar(other), horsePower(other.horsePower), topSpeed(other.topSpeed){}

std::istream& operator>>(std::istream& is, CSportsCar& c) {
    is >> static_cast<CCar&>(c);

    if (c.getYear() < 1886) {
        throw CInvalidYear(c.getYear());
    }

    std::cout << "Enter horsePower: ";
    is >> c.horsePower;
    std::cout << "Enter topSpeed: ";
    is >> c.topSpeed;
    return is;
}

CSportsCar::CSportsCar()
    :horsePower(0), topSpeed(0){}