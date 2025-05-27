//
// Created by andrei-cristea on 5/26/25.
//

#include "CRallyCar.h"
#include "CInvalidYear.h"

CRallyCar::CRallyCar(const std::string &b, const std::string &m,const int y,const double r,const bool t)
    :CCar(b,m,y), rearTractionRatio(r), turbocharged(t){}


double CRallyCar::basePrice() const {
    return 10000 + 5000 * static_cast<int>(turbocharged);
}

std::string CRallyCar::getTypeName() const {
    return "Rally";
}

CRallyCar::CRallyCar(const CRallyCar &other)
    :CCar(other), rearTractionRatio(other.rearTractionRatio),turbocharged(other.turbocharged){}

std::istream& operator>>(std::istream& is, CRallyCar& c) {
    is >> static_cast<CCar&>(c);

    if (c.getYear() < 1886) {
        throw CInvalidYear(c.getYear());
    }

    std::cout << "Enter rearTractionRatio: ";
    is >> c.rearTractionRatio;
    std::cout << "Enter turbocharged (0/1): ";
    is >> c.turbocharged;
    return is;
}

CRallyCar::CRallyCar()
    :rearTractionRatio(0), turbocharged(false){}

bool CRallyCar::isTurbocharged() const {
    return turbocharged;
}