#pragma once

#include <string>
#include "common/exceptions/Exception.h"

const char QPSERR_INVALID_QUERY[] = "Invalid Query";

class QpsException : public Exception {
private:
    explicit QpsException(const std::string &msg) : Exception(msg) {}

public:
    static QpsException InvalidQueryException();
};
