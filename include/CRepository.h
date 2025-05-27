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

    void displayAll() {
        for (const auto& e : data) {
            std::cout << e << "\n";
        }
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
};

#endif // CREPOSITORY_H