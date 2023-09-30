#include "catch.hpp"
#include "qps/abstraction/ParentsStarAbstraction/ParentsStarAbstraction.h"
#include "../../mocks/MockPKBReader.h"
#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../AbstractionTestUtils.h"
#include "ParentsStarAbstractionTestData.h"

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Synonym)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
    REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_STARS_VECTOR);
    REQUIRE(resultTable.getColNames().size() == 2);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
    REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Integer)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentStarOf = MOCK_PARENT_CHILD_STARS_PAIRS;
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
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_STARS_COL_1);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Integer)_no_immediate_parent") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentStarOf = {};
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
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Synonym, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_STARS_COL_1);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Synonym)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
    REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockChildrenStar = MOCK_PARENT_CHILD_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_STARS_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Integer)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockIsParentStar = true;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Integer)_false") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockIsParentStar = false;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          FOLLOWS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockChildrenStar = MOCK_PARENT_CHILD_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Integer, Wildcard)_empty") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_STARS_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Integer)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentStarOf = MOCK_PARENT_CHILD_STARS_PAIRS;
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
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Integer)_no_immediate_parent") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
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
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsStarAbstraction - Parents*(Wildcard, Wildcard)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_STAR_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsStarAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableWildcard() == false);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
