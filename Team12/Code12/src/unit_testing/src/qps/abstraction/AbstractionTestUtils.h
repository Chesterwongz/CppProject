#pragma once

#include "qps/abstraction/IAbstraction.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/argument/argumentFactory/ArgumentFactory.h"
#include "../mocks/MockPKBReaderData.h"
#include "../mocks/MockPKBReader.h"
#include "../testUtils/argumentFactory/ArgumentFactory.h"
unique_ptr<AbstractionParams> createMockAbstractionParams(
        MockPKBReader &mockReader,
        Context &mockContext,
        Abstraction abstraction,
        AbstractArgument &firstArgument,
        AbstractArgument &secondArgument);
