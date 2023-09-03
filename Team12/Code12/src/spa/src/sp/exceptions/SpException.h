#pragma once

#include <string>
#include "common/exceptions/Exception.h"

class SpException : public Exception {
public:
    static inline const std::string type = "SpException";

    explicit SpException(const std::string &msg) : Exception(msg) {}
};