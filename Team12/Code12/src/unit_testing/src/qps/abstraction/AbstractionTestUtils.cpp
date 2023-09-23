#include "AbstractionTestUtils.h"

unique_ptr<AbstractionParams> createMockAbstractionParams(
        MockPKBReader &mockReader,
        Abstraction abstraction,
        IArgument &firstArgument,
        IArgument &secondArgument,
        bool isTransitive) {
    Context mockContext = Context();
    if (!firstArgument.isWildcard()) {
        mockContext.addToken(firstArgument.getValue(), "stmt");
    }
    if (!secondArgument.isWildcard()) {
        mockContext.addToken(secondArgument.getValue(), "stmt");
    }
    unique_ptr<AbstractionParams> abstractionParams
            = std::make_unique<AbstractionParams>(
                    mockReader,
                    std::move(mockContext),
                    abstraction,
                    firstArgument,
                    secondArgument,
                    isTransitive);
    return abstractionParams;
}
