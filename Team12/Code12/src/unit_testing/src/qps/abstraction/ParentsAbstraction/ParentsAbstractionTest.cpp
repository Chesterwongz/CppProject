#include "catch.hpp"
#include "qps/abstraction/ParentsAbstraction/ParentsAbstraction.h"
#include "../../mocks/MockPKBReader.h"
#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../AbstractionTestUtils.h"
#include "ParentsAbstractionTestData.h"

TEST_CASE("ParentsAbstraction - getAbstractions - Parents(Synonym, Synonym_EMPTY)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    ParentsAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
    REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("ParentsAbstraction - getAbstractions - Parents(Synonym, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildPairs = MOCK_PARENT_CHILD_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    ParentsAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_VECTORS);
    REQUIRE(resultTable.getColNames().size() == 2);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
    REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsAbstraction - getAbstractions - Parents(Synonym, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildPairs = MOCK_PARENT_CHILD_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    ParentsAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_COL_1);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("ParentsAbstraction - getAbstractions - Parents(Wildcard, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildPairs = MOCK_PARENT_CHILD_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    ParentsAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsAbstraction - getAbstractions - Parents(Wildcard, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildPairs = MOCK_PARENT_CHILD_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    ParentsAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsAbstraction - getAbstractions - Parents(Wildcard, Wildcard)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    ParentsAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.isTableWildcard() == false);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsAbstraction - getAbstractions - Parents*(Wildcard, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildStarPairs = MOCK_PARENT_CHILD_STARS_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, true);

    ParentsAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_STARS_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}
