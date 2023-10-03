#pragma once

#include <string>
#include <string_view>

#include "SpException.h"

class SpParsingFailedException : public SpException {
 public:
  static inline constexpr string_view type = "UndefinedProcCallException";

  explicit SpParsingFailedException() : SpException("Failed to parse input.") {}
};