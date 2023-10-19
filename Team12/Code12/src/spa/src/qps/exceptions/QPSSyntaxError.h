#include <string>

#include "QPSException.h"

const char QPS_TOKENIZATION_ERR[] =
    "Error occurred during tokenization, invalid token: ";
const char QPS_TOKENIZATION_ERR_INCOMPLETE_DECLARATION[] =
    "Incomplete declaration";
const char QPS_TOKENIZATION_ERR_INCOMPLETE_SELECT[] = "Incomplete Select";
const char QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT[] = "Incorrect arguments";
const char QPS_TOKENIZATION_ERR_INCOMPLETE_QUERY[] = "Incomplete query";
const char QPS_TOKENIZATION_ERR_NAME[] = "Name token is invalid: ";
const char QPS_TOKENIZATION_ERR_SYNONYM[] = "Synonym is invalid: ";
const char QPS_TOKENIZATION_ERR_ATTR_REF[] = "AttrRef is invalid: ";
const char QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH[] =
    "Invalid Pattern Expression";
const char QPS_SYNTAX_ERR_AND[] = "and should appear after a clause";

class QPSSyntaxError : public QPSException {
 public:
  explicit QPSSyntaxError(const std::string &errorMessage)
      : QPSException(errorMessage) {}
};
