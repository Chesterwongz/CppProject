#pragma once

#include <string>
#include <string_view>
#include "SpException.h"

class UndefinedProcCallException : public SpException {
public:
    static inline constexpr string_view type = "UndefinedProcCallException";

    explicit UndefinedProcCallException(const string &name)
        : SpException("Procedure name '" + name + "' called has not been defined in the program!") {}
};