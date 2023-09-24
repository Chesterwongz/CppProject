#include "QPSException.h"


// TODO: better exception splitting
const char QPS_INVALID_QUERY_ERR_UNMATCHED_QUOTE[] = "Unmatched quote";
const char QPS_INVALID_QUERY_ERR_INVALID_TOKEN[] = "Invalid token";
const char QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN[] = "Unexpected token";
const char QPS_INVALID_QUERY_ERR_UNMATCHED_BRACKET[] = "Unmatched bracket";
const char QPS_INVALID_QUERY_ERR_INVALID_SYNONYM[] = "Invalid synonym";
const char QPS_INVALID_QUERY_ERR_EMPTY_LITERAL[] = "Empty literal";
const char QPS_INVALID_QUERY_ERR_OUT_OF_BOUNDS[] = "Out of bounds";
const char QPS_INVALID_QUERY_REPEAT_SYNONYM_NAME[] = "Repeated synonym name";
const char QPS_INVALID_QUERY_INAVLID_NAME[] = "Invalid Name";
const char QPS_INVALID_QUERY_INAVLID_INTEGER[] = "Invalid Integer";
const char QPS_INVALID_QUERY_INVALID_ENTITY[] = "Invalid entity: ";
const char QPS_INVALID_QUERY_INCOMPLETE_QUERY[] = "Incomplete query";
const char QPS_INVALID_QUERY_INVALID_PATTERN_SYNONYM[] = "Invalid pattern synonym";
const char QPS_INVALID_QUERY_INVALID_SELECT_SYNONYM[] = "Synonym you are selecting does not exist";
const char QPS_INVALID_QUERY_INCOMPLETE_PARTIAL_MATCH_PATTERN[] = "Your partial match should end and start with a wildcard";
const char QPS_INVALID_QUERY_MISSING_ARGUMENTS[] = "Your clause is incomplete, you might have missing arguments";

class QPSInvalidQueryException : public QPSException {
public:
	explicit QPSInvalidQueryException(const string &errorMsg) : QPSException(errorMsg) {}
};
