#pragma once

#include <string>
#include "SpException.h"

class UnexpectedTokenError : public SpException {
public:
    static inline const std::string type = "UnexpectedTokenError";

    UnexpectedTokenError(const std::string &expectedToken, const std::string &unexpectedToken)
        : SpException("Expected " + expectedToken + " but got " + unexpectedToken + " instead!") {}

    UnexpectedTokenError(const std::string &expectedToken)
            : SpException("Expected " + expectedToken + " but got nothing instead!") {}
};