#include "QPSException.h"

#include <string>

// TODO(QPS): better exception splitting
const char QPS_INVALID_QUERY_ERR_UNMATCHED_QUOTE[] = "Unmatched quote";
const char QPS_INVALID_QUERY_ERR_INVALID_TOKEN[] = "Invalid token";
const char QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN[] = "Unexpected token";
const char QPS_INVALID_QUERY_ERR_UNMATCHED_BRACKET[] = "Unmatched bracket";
const char QPS_INVALID_QUERY_ERR_INVALID_SYNONYM[] = "Invalid synonym";
const char QPS_INVALID_QUERY_ERR_EMPTY_LITERAL[] = "Empty literal";
const char QPS_INVALID_QUERY_ERR_OUT_OF_BOUNDS[] = "Out of bounds";
const char QPS_INVALID_QUERY_REPEAT_SYNONYM_NAME[] = "Repeated synonym name";
const char QPS_INVALID_QUERY_INVALID_NAME[] = "Invalid Name";
const char QPS_INVALID_QUERY_INVALID_INTEGER[] = "Invalid Integer";
const char QPS_INVALID_QUERY_INVALID_ENTITY[] = "Invalid entity: ";
const char QPS_INVALID_QUERY_INCOMPLETE_QUERY[] = "Incomplete query";
const char QPS_INVALID_QUERY_NO_CLAUSES[] = "No clauses found";
const char QPS_INVALID_QUERY_INVALID_PATTERN_SYNONYM[] =
    "Invalid pattern synonym";
const char QPS_INVALID_QUERY_NO_SELECT_SYNONYM[] = "No synonyms to  select";
const char QPS_INVALID_QUERY_INCOMPLETE_PARTIAL_MATCH_PATTERN[] =
    "Your partial match should end and start with a wildcard";
const char QPS_INVALID_QUERY_MISSING_ARGUMENTS[] =
    "Your clause is incomplete, you might have missing arguments";
const char QPS_INVALID_QUERY_INCORRECT_ARGUMENT[] =
    "Argument type is incorrect for Such That clause";

class QPSInvalidQueryException : public QPSException {
 public:
  explicit QPSInvalidQueryException(const std::string &errorMsg)
      : QPSException(errorMsg) {}
};
