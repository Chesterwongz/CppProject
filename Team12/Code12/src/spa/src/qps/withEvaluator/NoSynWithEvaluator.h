#pragma once

#include <memory>

#include "IWithEvaluator.h"

class NoSynWithEvaluator : public IWithEvaluator {
 protected:
  unique_ptr<AbstractArgument> firstArg;
  unique_ptr<AbstractArgument> secondArg;

  public:
  explicit NoSynWithEvaluator(unique_ptr<AbstractArgument> firstArg,
                                  unique_ptr<AbstractArgument> secondArg)
       : firstArg(move(firstArg)), secondArg(move(secondArg)) {};

  IntermediateTable evaluate(PKBReader& pkbReader) override;
};