#pragma once

#include <memory>

#include "../mocks/MockPKBReaderData.h"
#include "../testUtils/argumentFactory/ArgumentFactory.h"
#include "qps/abstraction/BaseAbstraction.h"

unique_ptr<AbstractionParams> createMockAbstractionParams(
    PKBReader &mockReader, Context &mockContext, Abstraction abstraction,
    AbstractArgument &firstArgument, AbstractArgument &secondArgument);

unique_ptr<AbstractionParams> createMockAbstractionParamsProc(
    PKBReader &mockReader, Context &mockContext, Abstraction abstraction,
    AbstractArgument &firstArgument, AbstractArgument &secondArgument);
