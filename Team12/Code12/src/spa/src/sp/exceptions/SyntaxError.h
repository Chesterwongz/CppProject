#pragma once

#include <string>
#include "SpException.h"

class SyntaxError : public SpException {
public:
    static inline const std::string type = "SyntaxError";

    SyntaxError(const char &unexpectedToken)
        : SpException("Syntax error! Unexpected token: " + std::string(1,unexpectedToken)) {}
};