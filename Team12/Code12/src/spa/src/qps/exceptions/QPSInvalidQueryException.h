#include "QPSException.h"

const char QPS_INVALID_QUERY_ERR_UNMATCHED_QUOTE[] = "Unmatched quote";
const char QPS_INVALID_QUERY_ERR_INVALID_TOKEN[] = "Invalid token";
const char QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN[] = "Unexpected token";
const char QPS_INVALID_QUERY_ERR_UNMATCHED_BRACKET[] = "Unmatched bracket";
const char QPS_INVALID_QUERY_ERR_INVALID_SYNONYM[] = "Invalid synonym";

class QPSInvalidQueryException : public QPSException {
public:
	explicit QPSInvalidQueryException(const string &errorMsg) : QPSException(errorMsg) {}
};
