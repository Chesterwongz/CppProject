#pragma once

#include <string>
#include <string_view>
#include "SpException.h"

class UnexpectedTokenException : public SpException {
public:
    static inline constexpr std::string_view type = "UnexpectedTokenException";

    explicit UnexpectedTokenException(const std::string &expectedToken, int lineNum)
            : SpException("Expected " + expectedToken + " at line " + std::to_string(lineNum) + "!") {}
};