#ifndef CREPOSITORY_H
#define CREPOSITORY_H

#include <vector>
#include <algorithm>
#include <iostream>

template<typename T>
class CRepository {
    std::vector<T> data;
public:
    void add(const T& element) {
        data.push_back(element);
    }

    void remove(const T& element) {
        data.erase(
            std::remove(data.begin(), data.end(), element),
            data.end()
        );
    }

    std::vector<T>& getAll() {
        return data;
    }

    template<typename Pred>
    std::vector<T> findAll(Pred pred) {
        std::vector<T> result;
        for (const auto& e : data) {
            if (pred(e))
                result.push_back(e);
        }
        return result;
    }

    void displayAll() {

        if (data.empty()) {
            std::cout << "No available cars for auctioning at the moment.\n";
        }
        else {
            std::cout<<"Cars available for auctioning:\n";
            for (const auto& e : data) {
                std::cout << *e;
                std::cout << "Type: "<<e ->getTypeName() << "\n"
                        <<"BasePrice: "<< e->basePrice() << "\n";

            }
        }
    }
};

#endif // CREPOSITORY_H