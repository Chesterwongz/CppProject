#pragma once

#include <string>
#include "SpException.h"

class SyntaxError : public SpException {
public:
    static inline constexpr string_view type = "SyntaxError";

    explicit SyntaxError(const char &unexpectedToken)
        : SpException("Syntax error! Unexpected token: " + string(1,unexpectedToken)) {}
};