#include <string>

#include "QPSException.h"

const char QPS_PARSER_ERR_SYN_ASSIGN_MISSING[] = "Missing syn assign";

class QPSParserError : public QPSException {
 public:
  explicit QPSParserError(const std::string &errorMessage)
      : QPSException(errorMessage) {}
};
