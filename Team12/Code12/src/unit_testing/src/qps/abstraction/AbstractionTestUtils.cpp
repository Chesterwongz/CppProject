#include "AbstractionTestUtils.h"
#include "qps/common/Keywords.h"

unique_ptr<AbstractionParams> createMockAbstractionParams(
        MockPKBReader &mockReader,
        Context &mockContext,
        Abstraction abstraction,
        IArgument &firstArgument,
        IArgument &secondArgument,
        bool isTransitive) {
    if (!firstArgument.isWildcard()) {
        mockContext.addSynonym(firstArgument.getValue(), STMT_ENTITY);
    }
    if (!secondArgument.isWildcard()) {
        mockContext.addSynonym(secondArgument.getValue(), STMT_ENTITY);
    }
    unique_ptr<AbstractionParams> abstractionParams
            = std::make_unique<AbstractionParams>(
                    mockReader,
                    mockContext,
                    abstraction,
                    firstArgument,
                    secondArgument,
                    isTransitive);
    return abstractionParams;
}
