#pragma once

#include <memory>

#include "qps/withEvaluator/WithEvaluator.h"
#include "WithEvaluatorFactory.h"

using std::unique_ptr;

class WithEvaluatorFactory {
 public:
  static unique_ptr<WithEvaluator> createWithEvaluator(
      unique_ptr<AbstractArgument> firstArg,
      unique_ptr<AbstractArgument> secondArg, PKBReader& pkbReader);
};
