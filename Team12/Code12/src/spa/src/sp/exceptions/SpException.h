#pragma once

#include <string>
#include "common/exceptions/Exception.h"

//const char SPERR_TOKEN_STARTS_WITH_DIGIT[] = "String token starts with digit";
//const char SPERR_INTEGER_STARTS_WITH_ZERO[] = "Integer token starts with zero";
//const char SPERR_UNKNOWN_TOKEN[] = "Unknown token";
//const char SPERR_INVALID_SOURCE_CHAR[] = "Invalid Source Character Detected";
//
//const char SPERR_END_OF_STREAM[] = "End of token stream";
//const char SPERR_UNEXPECTED_TOKEN[] = "Unexpected Token";
//const char SPERR_CONTEXT_ERROR[] = "Context Error";
//const char SPERR_PROCEDURE_SELF_CALL[] = "Procedure Self Call Error";

class SpException : public Exception {
public:
    static inline const std::string type = "SpException";

    SpException::SpException(const std::string &msg) : Exception(msg) {}
};