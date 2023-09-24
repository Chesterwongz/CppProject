#pragma once

#include "qps/abstraction/IAbstraction.h"
#include "qps/argument/argumentFactory/ArgumentFactory.h"
#include "../mocks/MockPKBReaderData.h"
#include "../mocks/MockPKBReader.h"

unique_ptr<AbstractionParams> createMockAbstractionParams(
        MockPKBReader &mockReader,
        Abstraction abstraction,
        IArgument &firstArgument,
        IArgument &secondArgument,
        bool isTransitive);
