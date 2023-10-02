#include "catch.hpp"
#include "qps/abstraction/FollowsStarAbstraction/FollowsStarAbstraction.h"
#include "../../mocks/MockPKBReader.h"
#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../AbstractionTestUtils.h"
#include "FollowsStarAbstractionTestData.h"

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Synonym)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
    REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsStarPairs = MOCK_FOLLOWS_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_STARS_VECTOR);
    REQUIRE(resultTable.getColNames().size() == 2);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
    REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}


TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Integer)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowedStar = MOCK_FOLLOWS_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_FOLLOWED_STAR_COL_1);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Integer) not followed") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}


TEST_CASE("FollowsStarAbstraction - Follows*(Synonym, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsStarPairs = MOCK_FOLLOWS_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_FOLLOWED_STAR_COL_1);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsStar = MOCK_FOLLOWS_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_STARS_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Synonym)_no followed") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsStar = MOCK_FOLLOWS_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Wildcard)_no followed") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Integer)_true") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockIsFollowsStar = true;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Integer, Integer)_false") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockIsFollowsStar = false;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsStarPairs = MOCK_FOLLOWS_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_STARS_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Integer)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowedStar = MOCK_FOLLOWS_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Integer) not followed") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsStarPairs = MOCK_FOLLOWS_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsStarAbstraction - Follows*(Wildcard, Wildcard)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    FollowsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableWildcard() == false);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
