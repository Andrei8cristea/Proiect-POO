//
// Created by andrei-cristea on 5/26/25.
//

#ifndef CSTRATEGY_H
#define CSTRATEGY_H



class CStrategy {
public:

    enum class Mode {Normal, Aggressive, Passive };

    static CStrategy normal() { return CStrategy(1.15, 1.05, Mode::Normal);}

    static CStrategy aggressive() {return CStrategy(1.75, 1.25, Mode::Aggressive);}

    static CStrategy passive() {return CStrategy(1.0, 0.8, Mode::Passive); }

    CStrategy(double f, double o, Mode m);

    CStrategy();

    double adjustFavourite(double baseBid) const;

    double adjustOther(double baseBid) const;

    Mode getMode() const;

private:

    double favCoef;
    double othersCoef;

    Mode current;

};



#endif //CSTRATEGY_H
