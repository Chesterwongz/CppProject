#pragma once

#include <memory>

#include "qps/withEvaluator/WithEvaluator.h"
#include "WithEvaluatorFactory.h"

using std::unique_ptr;

class WithEvaluatorFactory {
 public:
  static unique_ptr<WithEvaluator> createWithEvaluator(
      AbstractArgument& firstArg,
      AbstractArgument& secondArg, PKBReader& pkbReader);
};
