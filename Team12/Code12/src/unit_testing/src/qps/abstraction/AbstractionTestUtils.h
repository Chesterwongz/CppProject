#pragma once

#include <memory>

#include "../mocks/MockPKBReaderData.h"
#include "qps/abstraction/BaseAbstraction.h"

unique_ptr<AbstractionParams> createMockAbstractionParams(
    PKBReader &mockReader, Abstraction abstraction,
    AbstractArgument &firstArgument, AbstractArgument &secondArgument);
