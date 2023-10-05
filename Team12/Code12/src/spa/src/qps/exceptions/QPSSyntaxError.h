#include "QPSException.h"

const char QPS_TOKENIZATION_ERR[] = "Error occurred during tokenization, invalid token: ";
const char QPS_TOKENIZATION_ERR_INCOMPLETE_DECLARATION[] = "Incomplete declaration";
const char QPS_TOKENIZATION_ERR_INCOMPLETE_SELECT[] = "Incomplete Select";
const char QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT[] = "Incorrect arguments";
const char QPS_TOKENIZATION_ERR_INTEGER_ZERO[] = "Integer token starts with zero: ";
const char QPS_TOKENIZATION_ERR_NAME[] = "Name token is invalid: ";
const char QPS_TOKENIZATION_ERR_IDENT[] = "Invalid Ident";
const char QPS_TOKENIZATION_ERR_EMPTY_QUOTE[] = "Empty quotes";
const char QPS_TOKENIZATION_ERR_UNMATCHED_QUOTE[] = "Unmatched quotes";
const char QPS_TOKENIZATION_ERR_UNMATCHED_BRACKETS[] = "Unmatched brackets";
const char QPS_SYNTAX_ERR_INVALID_PATTERN_SYN[] = "Invalid Pattern synonym type";

class QPSSyntaxError : public QPSException {
public:
    explicit QPSSyntaxError(const std::string &errorMessage) : QPSException(errorMessage) {}
};


