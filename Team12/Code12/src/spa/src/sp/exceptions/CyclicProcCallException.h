#pragma once

#include <string>
#include <string_view>

#include "SpException.h"

class CyclicProcCallException : public SpException {
 public:
  static inline constexpr string_view type = "CyclicProcCallException";

  CyclicProcCallException()
      : SpException("Cyclic procedure calls detected!") {}
};
