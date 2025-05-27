//
// Created by andrei-cristea on 5/26/25.
//

#ifndef CBIDDER_H
#define CBIDDER_H

#include <string>
#include <iostream>
#include <memory>
#include <list>
#include "CStrategy.h"
#include "CCar.h"


class CBidder {
    std::string name;
    double budget;
    std::string favourite;
    CStrategy strategy;

    static int nextId;
    int id;

    std::list<std::shared_ptr<CCar>> acquired;
    int roundsWithoutWin = 0;

public:
    CBidder(const std::string& n, double b, const std::string& f, CStrategy s);

    CBidder();

    friend std::istream& operator>>(std::istream& is, CBidder& b);

    double decideBid(const CCar& car, double currentPrice) const;

    const std::string& getName() const;

    double getBudget() const;

    void setBudget(double newBudget);

    static int totalBidders();

    void addAcquired(const std::shared_ptr<CCar>& car);

    const std::list<std::shared_ptr<CCar>> getAcquired () ;

    void wonRound();

    void lostRound();

    int getRoundsLost() const;
};



#endif //CBIDDER_H
