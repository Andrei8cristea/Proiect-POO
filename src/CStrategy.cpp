//
// Created by andrei-cristea on 5/26/25.
//

#include "CStrategy.h"


CStrategy::CStrategy(const double f,const double o,const Mode m)
    :favCoef(f),othersCoef(o), current(m){}

// CStrategy::CStrategy(double f, double o)
//     :favCoef(f),othersCoef(o){}

CStrategy::CStrategy():favCoef(1.0),othersCoef(1.0),current() {}

double CStrategy::adjustFavourite(double const baseBid) const {
    return baseBid * favCoef;
}

double CStrategy::adjustOther(double const baseBid) const {
    return baseBid * othersCoef;
}

CStrategy::Mode CStrategy::getMode() const {
    return current;
}