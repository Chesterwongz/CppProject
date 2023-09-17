#pragma once

#include <string>
#include "common/exceptions/Exception.h"

class QPSException : public Exception {
protected:
    explicit QPSException(const std::string& msg) : Exception(msg) {}
}
