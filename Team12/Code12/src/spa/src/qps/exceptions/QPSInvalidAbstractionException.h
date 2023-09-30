#include "QPSException.h"

const char QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE[] = "abstraction does not support the argument types given";
const char QPS_INVALID_ABSTRACTION_ERR_NON_STATEMENT_TYPE[] = "abstraction expected statement/wildcard type";
const char QPS_INVALID_ABSTRACTION_ERR_UNKNOWN_ARG_PERMUTATION[] = "unknown argument permutation";
const char QPS_INVALID_ABSTRACTION_ERR_UNKNOWN_ABSTRACTION[] = "unknown abstraction";

class QPSInvalidAbstractionException : public QPSException {
public:
	explicit QPSInvalidAbstractionException(const std::string &errorMsg) : QPSException(errorMsg) {}
};
