#pragma once

#include <string>

#include "Exception.h"

class CommonSyntaxError : public Exception {
 public:
  static inline constexpr std::string_view type = "CommonSyntaxError";

  explicit CommonSyntaxError(const std::string &msg)
      : Exception("Syntax error: Invalid token '" + msg + "'!") {}
};
