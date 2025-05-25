//
// Created by andrei-cristea on 5/23/25.
//

#include "../include/CCar.h"

#include <string>
#include <iostream>


CCar::CCar(const std::string &b, const std::string &m, const int y)
        : brand(b), model(m), year(y) {}

std::ostream& operator<<(std::ostream& os, const CCar& car) {

    os
    << "\nBrand: "<< car.brand
    << "\nModel: "<< car.model
    << "\nYear: "<< car.year
    <<std::endl;
    return os;

}

std::istream &operator>>(std::istream &is, CCar &car) {
    std::cout << "Enter brand: ";
    is >> car.brand;
    std::cout << "Enter model: ";
    is >> car.model;
    std::cout << "Enter year: ";
    is >> car.year;
    return is;

}


CCar::CCar(const CCar &other)
    :brand(other.brand),model(other.model),year(other.year){}

bool CCar::operator<(const CCar &other) const {
    return basePrice() < other.basePrice();
}

bool operator==(const CCar &a, const CCar &b) {
    return a.getTypeName() == b.getTypeName() && a.basePrice() == b.basePrice();
}

CCar::CCar()
    :brand("not_known"), model("not_known"), year(0){}

int CCar::getYear() const {
    return year;
}

CCar &CCar::operator=(const CCar &other) {
    brand = other.brand;
    model = other.model;
    year  = other.year;
    return *this;
}