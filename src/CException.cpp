//
// Created by andrei-cristea on 5/26/25.
//

#include "CException.h"

CException::CException(const std::string &m)
    :msg("Program error is : " + m){}

const char *CException::what() const noexcept{
    return msg.c_str();
}

//c_str convert string -> const char*
//