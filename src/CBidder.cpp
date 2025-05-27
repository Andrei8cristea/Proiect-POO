//
// Created by andrei-cristea on 5/26/25.
//

#include "CBidder.h"
#include "CInvalidBudget.h"
#include <random>

CBidder::CBidder(const std::string &n,const double b, const std::string &f, CStrategy s)
    :name(n), budget(b), favourite(f), strategy(s), id(nextId++){}

CBidder::CBidder(): name("Default"), budget(0), favourite("Not_known"), id(nextId++)  {}


std::istream& operator>>(std::istream& is , CBidder& b) { //not const because of budget
    std::cout<<"Please enter your following details:\n";
    std::cout<<"\nName: ";
    is >> b.name;
    std::cout<<"\nBudget: ";
    is >>b.budget;

    if (b.budget > 999999.00 || b.budget < 1.00) {
        throw CInvalidBudget(b.budget);
    }
    // std::cout<<"\nFavourite car type(\"Classic\"/\"Sports\"/\"Rally\"): ";
    // is >> b.favourite;

    b.strategy = CStrategy(); // smth default because the user will get to choose

    return is;
}

double CBidder::decideBid(const CCar &car, double const currentPrice) const {
    //I consider a valid bid if it is 500 more than the current one
    // double base = currentPrice + 500;
    // if (car.getTypeName() == favourite) {
    //     return std::min(strategy.adjustFavourite(base), budget);
    // }
    // else {
    //     return std::min(strategy.adjustOther(base), budget);
    // }

    //double favCoef, othCoef;
    bool const isFav = car.getTypeName() == favourite;
    unsigned long int const wonCount = acquired.size();
    int const lostRounds = roundsWithoutWin;

    CStrategy strat;
    if (lostRounds >=1 && isFav) {
        //aggressive
        strat = CStrategy::aggressive();
    }

    else if (wonCount >= 1 && !isFav) {
        //normal
        strat = CStrategy::normal();
    }

    else {
        //passive
        strat = CStrategy::passive();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution dist(0.0, 1000.0);
    double const stressFactor = dist(gen);

    //for debug:
    // std::cout << "  [" << name << " Strategy: "
    //           << (strat.getMode() == CStrategy::Mode::Aggressive ? "Aggressive" :
    //               strat.getMode() == CStrategy::Mode::Normal     ? "Normal"     :
    //                                                                "Passive")
    //           << "]\n";

    double const base = currentPrice + 500;
    double const offer = isFav ? strat.adjustFavourite(base) : strat.adjustOther(base);
    double const finalOffer = std::min(offer + stressFactor, budget);



    return finalOffer;



}

const std::string &CBidder::getName() const{
    return name;
}

double CBidder::getBudget() const {
    return budget;
}

void CBidder::setBudget(double const newBudget) {
    budget = newBudget;
}

int CBidder::totalBidders() {
    return nextId;
}

void CBidder::addAcquired(const std::shared_ptr<CCar> &car) {
    acquired.push_back(car);
}

const std::list<std::shared_ptr<CCar> > CBidder::getAcquired() const {
    return acquired;
}

void CBidder::wonRound() {
    roundsWithoutWin = 0;
}

void CBidder::lostRound() {
    roundsWithoutWin++;
}


int CBidder::getRoundsLost() const {
    return roundsWithoutWin;
}




int CBidder::nextId = 0;
