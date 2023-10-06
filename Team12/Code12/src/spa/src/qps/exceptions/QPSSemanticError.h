#include "QPSException.h"

#include <string_view>

const char QPS_SEMANTIC_ERR_REPEATED_SYNONYM[] =
    "Repeated synonym during declaration: ";
const char QPS_SEMANTIC_ERR_UNDECLARED_SYNONYM[] = "Using undeclared synonym: ";
const char QPS_SEMANTIC_ERR_NOT_STMT_SYN[] = "Not a stmt synonym";
const char QPS_SEMANTIC_ERR_NOT_VAR_SYN[] = "Not a var synonym";
const char QPS_SEMANTIC_ERR_WILDCARD_FIRSTARG[] =
    "Wildcard cannot be first argument";

class QPSSemanticError : public QPSException {
 public:
  static inline constexpr std::string_view type = "QPSSemanticError";

  explicit QPSSemanticError(const std::string &errorMessage)
      : QPSException(errorMessage) {}
};
