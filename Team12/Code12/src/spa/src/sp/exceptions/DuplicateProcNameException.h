#pragma once

#include <string>
#include <string_view>
#include "SpException.h"

class DuplicateProcNameException : public SpException {
public:
    static inline constexpr string_view type = "DuplicateProcNameException";

    explicit DuplicateProcNameException(const string &name)
            : SpException("Duplicate procedure name '" + name + "' This name has already been used!") {}
};