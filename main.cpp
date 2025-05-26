#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include <list>
#include <random>

#include "include/CCar.h"


class CException : public std::exception {
    std::string msg;
public:
    CException(const std::string& m);

    const char* what() const noexcept override;
};

CException::CException(const std::string &m)
    :msg("Program error is : " + m){}

const char *CException::what() const noexcept{
    return msg.c_str();
}
//c_str convert string -> const char*
//



class CInvalidYear final : public CException {
public:
    CInvalidYear(int year);
};

CInvalidYear::CInvalidYear(const int year)
    :CException("Invalid year " + std::to_string(year) + " is not >= 1886"){}


class CInvalidBudget final: public  CException {
public:
    CInvalidBudget(int budget);
};
CInvalidBudget::CInvalidBudget(int const budget)
    :CException("Invalid budget. Budget cannot be  " +std::to_string(budget) +  " \nYour budget must be in between 1 and 999999"){}

//######################################################################

















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

//#################

class CSportsCar final : public CCar {
    int horsePower;
    int topSpeed;

public:
    CSportsCar(const std::string& b, const std::string& m,
        int y, int h, int t);

    double basePrice() const override;

    std::string getTypeName() const override;

    CSportsCar(const CSportsCar& other);

    friend std::istream& operator>>(std::istream& is, CSportsCar& c);

    CSportsCar();

};

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

//####################
class CRallyCar final: public CCar {
    double rearTractionRatio;
    bool turbocharged;

public:
    CRallyCar(const std::string& b, const std::string& m,
        int y, double r, bool t);

    double basePrice() const override;

    std::string getTypeName() const override;

    CRallyCar(const CRallyCar& other);

    friend std::istream& operator>>(std::istream& is, CRallyCar& c);

    CRallyCar();

    bool isTurbocharged() const;

};
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

//###########################################################################

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

CStrategy::CStrategy(const double f,const double o,const Mode m)
    :favCoef(f),othersCoef(o), current(m){}

// CStrategy::CStrategy(double f, double o)
//     :favCoef(f),othersCoef(o){}

CStrategy::CStrategy():favCoef(1.0),othersCoef(1.0) {}

double CStrategy::adjustFavourite(double const baseBid) const {
    return baseBid * favCoef;
}

double CStrategy::adjustOther(double const baseBid) const {
    return baseBid * othersCoef;
}

CStrategy::Mode CStrategy::getMode() const {
    return current;
}

//#########################

// class CDynamicStrategy: public CStrategy {
//     std::unique_ptr<CStrategy> currentStrategy;
//
// public:
//     CDynamicStrategy();
//
//     int decide();
// };




//#########################


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

const std::list<std::shared_ptr<CCar> > CBidder::getAcquired()  {
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


//############################################################################3




//################################################################3
template<typename T>
class CRepository {
    std::vector<T> data;

public:
    void add(const T& element);
    void remove(const T& element);
    void displayAll();
    std::vector<T>& getAll();
    template<typename Pred>
    std::vector<T> findAll(Pred pred);
};

template<typename T>
void CRepository<T>::add(const T& element) {
    data.push_back(element);
}

template<typename T>
void CRepository<T>::remove(const T& element) {
    data.erase(
        std::remove(data.begin(), data.end(), element),
        data.end()
    );
}

template<typename T>
void CRepository<T>::displayAll() {
    for (const T& element : data) {
        std::cout << element;
        std::cout << "\n";
    }
}

template<typename T>
template<typename Pred>
std::vector<T> CRepository<T>::findAll(Pred pred) {
    std::vector<T> result;
    for (const auto& element : data) {
        if (pred(element)) {
            result.push_back(element);
        }
    }
    return result;
}

template<typename T>
std::vector<T> &CRepository<T>::getAll() {
    return data;
}



//########################################






//#################################################################


class CMenu {

private:
    CRepository<std::shared_ptr<CCar>>  carRepo;
    // CRepository<CAuction>               auctionRepo;
    CRepository<CBidder>               bidders;
    CBidder userBidder;
    bool userInitialized = false;

    CMenu ();

    void case1();

    void case2();

    void case3();

    void case4();

    void initData();

    static void showMenu();

    void handleInput();

public:


    //#######
    static CMenu& Instance();

    CMenu(const CMenu&) = delete;
    CMenu operator=(const CMenu&) = delete;

    void run();



};

CMenu::CMenu() {
    initData();
}

CMenu &CMenu::Instance() {
    static CMenu instance;
    //std::cout<< "Initialized";
    return instance;
}



void CMenu::initData() {

    // initializing cars
    carRepo.add(std::make_shared<CClassicCar>
        ("Ford", "Model T", 1925, 1.8, "USA" ));
    carRepo.add(std::make_shared<CRallyCar>(
        "Subaru", "Impreza", 2020, 0.8, true));


    // initializing bidders


    bidders.add(CBidder(
        "Alice" , 50000.0, "Classic" , CStrategy(1.2, 1.0, CStrategy::Mode::Normal)
    ));

    bidders.add(CBidder(
        "Boris" , 80000.0, "Rally", CStrategy(1.3 , 1.0, CStrategy::Mode::Normal)
    ));

    // bidders.add(CBidder(
    //     "Alice" , 50000.0, "Classic" , CStrategy(1.2, 1.0)
    // ));
    //
    // bidders.add(CBidder(
    //     "Boris" , 80000.0, "Rally", CStrategy(1.3 , 1.0)
    // ));

    // initializing auctions
}

void CMenu::showMenu() {
    std::cout << "Select one from the following options:\n";
    std::cout << "0. Exit\n";
    std::cout << "1. Sell a car\n";
    std::cout << "2. Watch the cars available for auctioning\n";
    std::cout << "3. Start the auctions\n";
    std::cout << "4. Show profile info\n";
    std::cout << "\n";
    std::cout<<"Your option: ";
}
void CMenu::case1() {
    // CCar sellingCar;
    //
    // std::cout<< "Enter details for the car you want to sell:\n";
    // try {
    //     std::cin >> sellingCar;
    //     if (sellingCar.getYear()< 1886) {
    //         throw CInvalidYear(sellingCar.getYear());
    //     }
    // }
    std::cout << "Choose car type to sell:\n"
              << " 1) ClassicCar\n"
              << " 2) SportsCar\n"
              << " 3) RallyCar\n"
              << "Enter choice: ";
    int choice;
    std::cin >> choice;

    try {
        switch (choice) {
            case 1: {
                CClassicCar car;
                std::cin>>car;
                carRepo.add(std::make_shared<CClassicCar>(car));
                std::cout<<"ClassicCar added.\n";
                break;
            }
            case 2: {
                CSportsCar car;
                std::cin >> car;
                carRepo.add(std::make_shared<CSportsCar>(car));
                std::cout << "SportsCar added.\n";
                break;
            }
            case 3: {
                CRallyCar car;
                std::cin >> car;
                carRepo.add(std::make_shared<CRallyCar>(car));
                std::cout << "RallyCar added.\n";
                break;
            }
            default:
                std::cout << "Invalid choice, returning to menu.\n";
        }
    }
    catch (const CInvalidYear& y) {
        std::cerr << y.what() << "\n";
    }
    catch (const CException& e) {
        std::cerr << e.what() << "\n";
    }

}

void CMenu::case2() {
    auto const allCars = carRepo.findAll([](const auto&) {return true;});

    if (allCars.empty()) {
        std::cout << "No cars available for auction.\n";
        return;
    }

    std::cout<<"Cars available for auctioning:\n";
    for (auto& ptr : allCars) {
        std::cout<<*ptr;
        std::cout << "Type: "<<ptr ->getTypeName() << "\n"
                    <<"BasePrice: "<< ptr->basePrice() << "\n";

        std::cout << "\n\n" ;
    }
}




void CMenu::case3() {
    // creating userBidder instance
    while (!userInitialized) {
        try{
            std::cout << std::endl;
            std::cin >> userBidder;
            bidders.add(userBidder);
            userInitialized = true;
        }
        catch (const CInvalidBudget& b) {
            std::cerr << b.what() << std::endl;
            std::cin.clear();
            std::string trash;
            std::getline(std::cin, trash);
            std::cout<< "Try again.\n";
        }
    }

    auto& allBidders = bidders.getAll();

    std::cout<<"\nThe auctions start with "<<CBidder::totalBidders()<<" bidders participating.\n";
    // getter for cars
    auto cars = carRepo.findAll([](auto& ){return true;});

    std::sort(cars.begin(), cars.end(),
  [](auto& a, auto& b){ return *a < *b; }
    );
    // for every car I am opening an auction
    for (auto& carPtr : cars) {
        double currentPrice = carPtr->basePrice();
        CBidder* winner = nullptr;
        const CBidder* lastBidder = nullptr;


        std::cout <<  "\nAuction for:\n " << *carPtr;

        //down casting for all derived classes of CCar
        if (auto const rally = std::dynamic_pointer_cast<CRallyCar>(carPtr)) {
            std::cout << "Turbo: " <<(rally->isTurbocharged() ? "yes" : "no") << "\n";
        }


        std::cout << "\nStarting at "<< currentPrice << "\n\n";


        bool skipBid = false;
        while(true){

            CBidder& user = allBidders.back();
            bool anyBid = false;


            // Bots bidding stage

            for (int i = 0; i + 1 < (int)allBidders.size(); i++) {
                auto& b = allBidders[i];
                    double offer = b.decideBid(*carPtr , currentPrice);
                    if (offer > currentPrice && lastBidder != &b) {
                        currentPrice = offer;
                        winner = &b;
                        lastBidder = &b;
                        anyBid = true;
                        std::cout <<"\n! "<<b.getName()<<" bids "<< offer <<" !\n";
                    }
            }


            //If bots didn't bid (and user is winner ## not necessarily) break
            if (!anyBid && winner!= nullptr) {
                break;
            }


            if (skipBid == false ) {
                bool bidSuccesful = false;
                while ( bidSuccesful == false) {
                    std::cout << "\nYour turn! Current price: "
                          << currentPrice << "\n";
                    std::cout << "Enter your bid (0 = pass)(-1 = skip): ";

                    double userOffer;
                    std::cin >> userOffer;

                    if (userOffer > currentPrice && userOffer <= user.getBudget()) {
                        currentPrice = userOffer;
                        winner       = &user;
                        lastBidder = &user;
                        anyBid   = true;
                        std::cout << "\n! You bid " << userOffer << " !\n";
                        bidSuccesful = true;
                    } else if (userOffer == 0){
                        std::cout << "\nYou pass.\n";
                        bidSuccesful = true;
                    }
                    else if (userOffer == -1) {
                        std::cout << "\nYou have skipped the auction for the current car.\n";
                        skipBid = true;
                        bidSuccesful = true;
                    }
                    else if (userOffer > user.getBudget()){
                        std::cout << " You don't have this budget. Please try again.\n";
                    }
                    else if (userOffer <= currentPrice) {
                        std::cout << "You need to bid more to make it a valid bid. Please try again.\n";
                    }

                }
                if (!anyBid) {
                    break;
                }
            }


        }

        if (winner != nullptr) {
            for (auto& b : allBidders) {

                if (winner == &b) {
                    std::cout << "\n>>> Winner is " << winner->getName()
                              << " at price " << currentPrice << "\n";
                    winner->setBudget(winner->getBudget() - currentPrice);
                    winner -> addAcquired(carPtr);
                    carRepo.remove(carPtr);
                    b.wonRound();
                }
                else {
                    b.lostRound();
                }
            }
        }
        else {
            std::cout<<"No bids placed. Auction closed.\n";
        }
    }
    std::cout<<"\nNo more cars for sale at the moment.\n";

}

void CMenu::case4() {
    std::cout << "Enter bidder name: ";
    std::string reqName;
    std::cin >> reqName;

    auto matches = bidders.findAll([&](const CBidder& b){return b.getName() == reqName;});

    if (matches.size() == 0) {
        std::cout << "0 results\n\n";
        return;
    }
    if (matches.size() >= 2) {
        std::cout << "throw fatal error" ;
        return;
    }

    CBidder& b = matches.front();

    std::cout << "\nProfile for : " << b.getName() << std::endl;
    std::cout << "Remaining budget: " << b.getBudget() <<std::endl;
    std::cout << "Last streak of lost rounds: " << b.getRoundsLost() << std::endl;
    std::cout << "Won rounds : " << b.getAcquired().size() << std::endl;

    std::cout<< "GARAGE:\n";
    const auto& cars = b.getAcquired();

    if (cars.empty()) {
        std::cout << "Empty for the moment\n\n";
    }
    else {
        for (const auto& carPtr : cars) {
            std::cout<< *carPtr;
            std::cout<<"\n##############\n";
        }
    }
}



void CMenu::handleInput() {
    int option;

    do{
        showMenu();

        std::cin >> option;
        switch(option) {
            case 0: {
                std::cout << "Exiting...\n";
                exit(0);
            }
            case 1: {
                case1();
                break;
            }
            case 2: {
                case2();
                break;
            }
            case 3: {
                case3();
                break;
            }
            case 4 : {
                case4();
                break;
            }
            default: {
                std::cout << "Invalid option, please try again.\n";
                break;
            }
        }

    }while (option != 0);

}


void CMenu::run() {
    //initData();
    while (true) {
        handleInput();
    }
}



int main() {

    try {
        CMenu::Instance().run();
    }
    catch (const std::exception& e) {
        std::cerr << "Main Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
