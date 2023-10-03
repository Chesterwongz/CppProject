#pragma once

#include "../mocks/MockPKBReader.h"
#include "../mocks/MockPKBReaderData.h"
#include "../testUtils/argumentFactory/ArgumentFactory.h"
#include "qps/abstraction/BaseAbstraction.h"
unique_ptr<AbstractionParams> createMockAbstractionParams(
    MockPKBReader &mockReader, Context &mockContext, Abstraction abstraction,
    AbstractArgument &firstArgument, AbstractArgument &secondArgument);
