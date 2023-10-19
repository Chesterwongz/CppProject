#include <string>

#include "QPSException.h"

const char QPS_UNSUPPORTED_CROSS_PRODUCT_EXCEPTION[] =
    "Cross product not supported for tables with common columns";

class QPSIntermediateTableException : public QPSException {
 public:
  explicit QPSIntermediateTableException(const std::string &errorMsg)
      : QPSException(errorMsg) {}
};
