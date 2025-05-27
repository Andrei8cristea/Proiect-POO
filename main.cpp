#include <iostream>
#include <memory>
#include <exception>
#include "include/CMenu.h"


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
