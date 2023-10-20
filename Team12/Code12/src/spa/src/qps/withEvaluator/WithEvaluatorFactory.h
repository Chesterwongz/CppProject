#pragma once

#include <memory>

#include "IWithEvaluator.h"

using std::unique_ptr;

class WithEvaluatorFactory {
 public:
  static unique_ptr<IWithEvaluator> createWithEvaluator(
      unique_ptr<AbstractArgument> firstArg,
      unique_ptr<AbstractArgument> secondArg);
};
