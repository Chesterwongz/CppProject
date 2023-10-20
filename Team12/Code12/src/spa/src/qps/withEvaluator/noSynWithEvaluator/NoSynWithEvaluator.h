#pragma once

#include <memory>

#include "qps/withEvaluator/WithEvaluator.h"

class NoSynWithEvaluator : public WithEvaluator {
 protected:
  unique_ptr<AbstractArgument> firstArg;
  unique_ptr<AbstractArgument> secondArg;

  public:
  explicit NoSynWithEvaluator(unique_ptr<AbstractArgument> firstArg,
                                  unique_ptr<AbstractArgument> secondArg)
       : firstArg(move(firstArg)), secondArg(move(secondArg)) {};

  IntermediateTable evaluate(PKBReader& pkbReader) override;
};