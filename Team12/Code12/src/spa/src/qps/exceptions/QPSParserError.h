#include <string>

#include "QPSException.h"

const char QPS_PARSER_ERR_SYN_ASSIGN_MISSING[] = "Missing syn assign";
const char QPS_PARSER_ERR_SYN_IF_MISSING[] = "Missing syn if";

class QPSParserError : public QPSException {
 public:
  explicit QPSParserError(const std::string &errorMessage)
      : QPSException(errorMessage) {}
};
