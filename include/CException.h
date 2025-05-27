//
// Created by andrei-cristea on 5/26/25.
//

#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <exception>
#include <string>

class CException : public std::exception {
    std::string msg;
public:
    explicit CException(const std::string& m);

    const char* what() const noexcept override;
};



#endif //CEXCEPTION_H
