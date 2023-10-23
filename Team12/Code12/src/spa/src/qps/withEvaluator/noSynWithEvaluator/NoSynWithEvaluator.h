#pragma once

#include <memory>
#include <utility>

#include "qps/withEvaluator/WithEvaluator.h"

class NoSynWithEvaluator : public WithEvaluator {
 protected:
  unique_ptr<AbstractArgument> firstArg;
  unique_ptr<AbstractArgument> secondArg;

 public:
  explicit NoSynWithEvaluator(unique_ptr<AbstractArgument> firstArg,
                              unique_ptr<AbstractArgument> secondArg,
                              PKBReader& pkbReader)
      : WithEvaluator(pkbReader),
        firstArg(std::move(firstArg)),
        secondArg(std::move(secondArg)) {}

  IntermediateTable evaluate() override;
};
