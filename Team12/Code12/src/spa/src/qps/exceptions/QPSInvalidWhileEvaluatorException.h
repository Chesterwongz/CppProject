#include <string>

#include "QPSException.h"

const char QPS_INVALID_WHILE_EVALUATOR_EVALUATION[] =
    "this evaluator does not support this method call";

class QPSInvalidWhileEvaluatorException : public QPSException {
 public:
  explicit QPSInvalidWhileEvaluatorException(const std::string &errorMsg)
      : QPSException(errorMsg) {}
};
