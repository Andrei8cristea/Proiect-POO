//
// Created by andrei-cristea on 5/26/25.
//

#include "CMenu.h"
#include "CClassicCar.h"
#include "CRallyCar.h"
#include "CSportsCar.h"
#include "CException.h"
#include "CInvalidYear.h"
#include "CInvalidBudget.h"

#include <algorithm>

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
    for (const auto& ptr : allCars) {
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
  [](const auto& a,const auto& b){ return *a < *b; }
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