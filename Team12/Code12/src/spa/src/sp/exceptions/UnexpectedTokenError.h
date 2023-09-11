#pragma once

#include <string>
#include <string_view>
#include "SpException.h"

class UnexpectedTokenError : public SpException {
public:
    static inline constexpr string_view type = "UnexpectedTokenError";

    explicit UnexpectedTokenError(const string &expectedToken, const string &unexpectedToken)
        : SpException("Expected " + expectedToken + " but got " + unexpectedToken + " instead!") {}

    explicit UnexpectedTokenError(const string &expectedToken)
            : SpException("Expected " + expectedToken + " but got nothing instead!") {}
};