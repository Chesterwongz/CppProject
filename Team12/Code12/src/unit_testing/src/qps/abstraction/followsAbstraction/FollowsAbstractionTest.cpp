#include "catch.hpp"
#include "qps/abstractionEvaluator/AbstractionEvaluator.h"
#include "qps/abstraction/FollowsAbstraction/FollowsAbstraction.h"
#include "../../mocks/MockPKBReader.h"
#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../AbstractionTestUtils.h"
#include "FollowsAbstractionTestData.h"

TEST_CASE("FollowsAbstraction - Follows(Synonym, Synonym)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
    REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("FollowsAbstraction - Follows(Synonym, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);

    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_VECTORS);
    REQUIRE(resultTable.getColNames().size() == 2);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
    REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}


TEST_CASE("FollowsAbstraction - Follows(Synonym, Integer)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowed = MOCK_FOLLOWED;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);

    REQUIRE(resultTable.getData().size() == 1);
    REQUIRE(resultTable.getData().at(0).size() == 1);
    REQUIRE(resultTable.getData().at(0).at(0) == MOCK_FOLLOWED);
}

TEST_CASE("FollowsAbstraction - Follows(Synonym, Integer) not followed") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowed = MOCK_NO_FOLLOWED;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}


TEST_CASE("FollowsAbstraction - Follows(Synonym, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);

    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_COL_1);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowing = MOCK_FOLLOWED;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.getData().size() == 1);
    REQUIRE(resultTable.getData().at(0).size() == 1);
    REQUIRE(resultTable.getData().at(0).at(0) == MOCK_FOLLOWED);
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Synonym)_no followed") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowing = MOCK_NO_FOLLOWED;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowing = MOCK_FOLLOWED;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Wildcard)_no followed") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowing = MOCK_NO_FOLLOWED;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Integer)_true") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockIsFollows = true;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Integer, Integer)_false") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockIsFollows = false;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);

    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Integer)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowed = MOCK_FOLLOWED;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Integer) not followed") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowed = MOCK_NO_FOLLOWED;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows(Wildcard, Wildcard)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          false);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);

    REQUIRE(resultTable.isTableWildcard() == false);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("FollowsAbstraction - Follows*(Wildcard, Synonym)") {
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
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          true);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);

    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_STARS_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsAbstraction - Follows*(Synonym, Integer)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowedPairs = MOCK_FOLLOWS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          true);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_COL_1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("FollowsAbstraction - Follows*(Integer, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockFollowsStar = MOCK_FOLLOWS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          true);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.getData() == MOCK_FOLLOWS_COL_2);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("FollowsAbstraction - Follows*(Integer, Integer)") {
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
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          true);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("FollowsAbstraction - Follows*(Integer, Integer)_false") {
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
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2,
                                          true);

    FollowsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = AbstractionEvaluator::evaluate(abstraction);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
