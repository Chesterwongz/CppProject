#include <string>
#include <string_view>

#include "QPSException.h"

const std::string QPS_SEMANTIC_ERR_REPEATED_SYNONYM =
    "Repeated synonym during declaration: ";
const std::string QPS_SEMANTIC_ERR_UNDECLARED_SYNONYM =
    "Using undeclared synonym: ";
const char QPS_SEMANTIC_ERR_NOT_STMT_SYN[] = "Not a stmt synonym";
const char QPS_SEMANTIC_ERR_NOT_VAR_SYN[] = "Not a var synonym";
const char QPS_SEMANTIC_ERR_NOT_PROC_SYN[] = "Not a proc synonym";
const char QPS_SEMANTIC_ERR_WILDCARD_FIRSTARG[] =
    "Wildcard cannot be first argument";
const char QPS_SEMANTIC_ERR_INVALID_PATTERN_SYN[] =
    "Invalid Pattern synonym type";
const char QPS_SEMANTIC_ERR_INVALID_SELECT[] =
    "Select clause without declarations";
const char QPS_SEMANTIC_ERR_INVALID_ATTR_REF[] = "Invalid Attr Ref";
const char QPS_SEMANTIC_ERR_INVALID_WITH[] = "Different ref types";

class QPSSemanticError : public QPSException {
 public:
  static inline constexpr std::string_view type = "QPSSemanticError";

  explicit QPSSemanticError(const std::string &errorMessage)
      : QPSException(errorMessage) {}
};
