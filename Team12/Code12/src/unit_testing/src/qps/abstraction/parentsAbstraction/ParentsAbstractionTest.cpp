#include "catch.hpp"
#include "qps/abstraction/ParentsAbstraction/ParentsAbstraction.h"
#include "../../mocks/MockPKBReader.h"
#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../AbstractionTestUtils.h"
#include "ParentsAbstractionTestData.h"

TEST_CASE("ParentsAbstraction - Parents(Synonym, Synonym)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
    REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("ParentsAbstraction - Parents(Synonym, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildPairs = MOCK_PARENT_CHILD_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_VECTORS);
    REQUIRE(resultTable.getColNames().size() == 2);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
    REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsAbstraction - Parents(Synonym, Integer)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockImmediateParentOf = MOCK_IMMEDIATE_PARENT_OF;
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

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData().size() == 1);
    REQUIRE(resultTable.getData().at(0).size() == 1);
    REQUIRE(resultTable.getData().at(0).at(0) == MOCK_IMMEDIATE_PARENT_OF.first);
}

TEST_CASE("ParentsAbstraction - Parents(Synonym, Integer)_no_immediate_parent") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockImmediateParentOf = MOCK_INVALID_IMMEDIATE_PARENT;
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

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsAbstraction - Parents(Synonym, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildPairs = MOCK_PARENT_CHILD_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_COL_1);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("ParentsAbstraction - Parents(Integer, Synonym)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
    REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("ParentsAbstraction - Parents(Integer, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockImmediateChildrenOf = MOCK_PARENT_CHILD_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsAbstraction - Parents(Integer, Integer)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockIsParent = true;
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

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsAbstraction - Parents(Integer, Integer)_false") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockIsParent = false;
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

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsAbstraction - Parents(Integer, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockImmediateChildrenOf = MOCK_PARENT_CHILD_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsAbstraction - Parents(Integer, Wildcard)_empty") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_INTEGER_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsAbstraction - Parents(Wildcard, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildPairs = MOCK_PARENT_CHILD_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.getData() == MOCK_PARENT_CHILD_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("ParentsAbstraction - Parents(Wildcard, Integer)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockImmediateParentOf = MOCK_IMMEDIATE_PARENT_OF;
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

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsAbstraction - Parents(Wildcard, Integer)_no_immediate_parent") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockImmediateParentOf = MOCK_INVALID_IMMEDIATE_PARENT;
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

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("ParentsAbstraction - Parents(Wildcard, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockParentChildPairs = MOCK_PARENT_CHILD_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("ParentsAbstraction - Parents(Wildcard, Wildcard)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    Context mockContext = Context();
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader,
                                          mockContext,
                                          PARENTS_ENUM,
                                          *mockArgument1,
                                          *mockArgument2);

    ParentsAbstraction abstraction(*abstractionParams);
    IntermediateTable resultTable = abstraction.evaluate();

    REQUIRE(resultTable.isTableWildcard() == false);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
