#include "AbstractionTestUtils.h"

#include <memory>

#include "qps/common/Keywords.h"

unique_ptr<AbstractionParams> createMockAbstractionParams(
    MockPKBReader& mockReader, Abstraction abstraction,
    AbstractArgument& firstArgument, AbstractArgument& secondArgument) {
  unique_ptr<AbstractionParams> abstractionParams =
      std::make_unique<AbstractionParams>(mockReader, abstraction,
                                          firstArgument, secondArgument);
  return abstractionParams;
}

unique_ptr<AbstractionParams> createMockAbstractionParamsProc(
    MockPKBReader& mockReader, Abstraction abstraction,
    AbstractArgument& firstArgument, AbstractArgument& secondArgument) {
  unique_ptr<AbstractionParams> abstractionParams =
      std::make_unique<AbstractionParams>(mockReader, abstraction,
                                          firstArgument, secondArgument);
  return abstractionParams;
}
