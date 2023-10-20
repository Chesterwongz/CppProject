#pragma once

#include <memory>

#include "../mocks/MockPKBReader.h"
#include "../mocks/MockPKBReaderData.h"
#include "qps/abstraction/BaseAbstraction.h"

unique_ptr<AbstractionParams> createMockAbstractionParams(
    MockPKBReader &mockReader, Abstraction abstraction,
    AbstractArgument &firstArgument, AbstractArgument &secondArgument);
