#include <string>

#include "QPSException.h"

const char QPS_PARSER_ERR_SYN_ASSIGN_MISSING[] = "Missing syn assign";
const char QPS_PARSER_ERR_SYN_IF_MISSING[] = "Missing syn if";
const char QPS_PARSER_ERR_SYN_WHILE_MISSING[] = "Missing syn while";

class QPSParserError : public QPSException {
 public:
  explicit QPSParserError(const std::string &errorMessage)
      : QPSException(errorMessage) {}
};
