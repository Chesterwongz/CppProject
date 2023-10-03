#pragma once

#include <string>

#include "SpException.h"

class SyntaxError : public SpException {
 public:
  static inline constexpr std::string_view type = "SyntaxError";

  explicit SyntaxError(const std::string &msg)
      : SpException("Syntax error: Invalid token '" + msg + "'!") {}

  explicit SyntaxError(const std::string &msg, int lineNum)
      : SpException("Syntax error: Invalid " + msg + " at line " +
                    std::to_string(lineNum) + "!") {}
};