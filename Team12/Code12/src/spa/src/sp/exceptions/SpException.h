#pragma once

#include <string>
#include <string_view>

#include "common/exceptions/Exception.h"

using std::string, std::string_view;

class SpException : public Exception {
 public:
  static inline constexpr string_view type = "SpException";

  explicit SpException(const string &msg) : Exception(msg) {}
};