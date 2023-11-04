#pragma once

#include <memory>
#include <utility>

#include "qps/withEvaluator/WithEvaluator.h"

class NoSynWithEvaluator : public WithEvaluator {
 protected:
  AbstractArgument& firstArg;
  AbstractArgument& secondArg;

 public:
  explicit NoSynWithEvaluator(AbstractArgument& firstArg,
                              AbstractArgument& secondArg,
                              PKBReader& pkbReader)
      : WithEvaluator(pkbReader),
        firstArg(firstArg),
        secondArg(secondArg) {}

  IntermediateTable evaluate() override;
};
