#pragma once

#include <string>

#include "Exception.h"

const char QPS_TOKENIZATION_ERR_UNMATCHED_QUOTE[] = "Unmatched quotes";
const char QPS_TOKENIZATION_ERR_EMPTY_QUOTE[] = "Empty quotes";

class CommonSyntaxError : public Exception {
 public:
  static inline constexpr std::string_view type = "CommonSyntaxError";

  explicit CommonSyntaxError(const std::string &msg)
      : Exception("Syntax error: Invalid token '" + msg + "'!") {}
};
