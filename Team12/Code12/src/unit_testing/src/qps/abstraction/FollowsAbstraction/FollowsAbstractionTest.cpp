#include "catch.hpp"
#include "qps/abstraction/FollowsAbstraction/FollowsAbstraction.h"
#include "../../mocks/MockPKBReader.h"
#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../AbstractionTestUtils.h"
#include "FollowsAbstractionTestData.h"

TEST_CASE("FollowsAbstraction - getAbstractions - Follows(Synonym, Synonym)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
    REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("FollowsAbstraction - getAbstractions - Follows(Synonym, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_VECTORS);
    REQUIRE(resultTable.getColNames().size() == 2);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
    REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsAbstraction - getAbstractions - Follows(Synonym, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_COL_1);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("FollowsAbstraction - getAbstractions - Follows(Wildcard, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsAbstraction - getAbstractions - Follows(Wildcard, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - getAbstractions - Follows(Wildcard, Wildcard)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.isTableWildcard() == false);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - getAbstractions - Follows*(Wildcard, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowedStarPairs = MOCK_FOLLOWS_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, true);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_STARS_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}
