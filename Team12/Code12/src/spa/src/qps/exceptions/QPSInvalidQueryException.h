#include <string>

#include "QPSException.h"

class QPSInvalidQueryException : public QPSException {
 public:
  explicit QPSInvalidQueryException(const std::string &errorMsg)
      : QPSException(errorMsg) {}
};
