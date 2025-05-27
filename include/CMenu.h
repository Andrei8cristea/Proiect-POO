//
// Created by andrei-cristea on 5/26/25.
//

#ifndef CMENU_H
#define CMENU_H


#include <memory>

#include "CRepository.h"
#include "CBidder.h"
#include "CCar.h"


class CMenu {

private:
    CRepository<std::shared_ptr<CCar>>  carRepo;
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



#endif //CMENU_H
