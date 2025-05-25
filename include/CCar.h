//
// Created by andrei-cristea on 5/23/25.
//

#ifndef CCAR_H
#define CCAR_H

#include <iostream>
#include <string>

class CCar {

    std::string brand;
    std::string model;
    int year;

public:
    CCar(const std::string& b, const std::string& m, int y);

    friend std::ostream& operator<<(std::ostream&, const CCar&);

    friend std::istream& operator>>(std::istream&,  CCar&);

    virtual double basePrice() const = 0;

    virtual std::string getTypeName() const = 0;

    CCar(const CCar &other);

    bool operator<(const CCar& other) const;

    CCar();

    int getYear() const;

    CCar& operator=(const CCar& other);

    virtual ~CCar() {}
};



#endif //CCAR_H
