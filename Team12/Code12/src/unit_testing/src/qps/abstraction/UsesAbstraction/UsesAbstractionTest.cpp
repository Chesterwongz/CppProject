#include "catch.hpp"
#include "qps/abstraction/UsesAbstraction/UsesAbstraction.h"
#include "../../mocks/MockPKBReader.h"
#include "../../intermediateTable/IntermediateTableTestUtils.h"
#include "../AbstractionTestUtils.h"
#include "UsesAbstractionTestData.h"

TEST_CASE("UsesAbstraction - getAbstractions - Uses(Synonym, Synonym)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    UsesAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
    REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("UsesAbstraction - getAbstractions - Uses(Synonym, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockAllUsedVariables = MOCK_USED_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    UsesAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData() == MOCK_USED_VECTORS);
    REQUIRE(resultTable.getColNames().size() == 2);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
    REQUIRE(resultTable.getColNames().at(1) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("UsesAbstraction - getAbstractions - Uses(Synonym, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockAllUsedVariables = MOCK_USED_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    UsesAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData() == MOCK_USED_VECTORS_COL_1);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("UsesAbstraction - getAbstractions - Uses(Synonym, Ident)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockStatementsUsing = MOCK_USING_STATEMENTS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    UsesAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData().size() == 3);
    REQUIRE(resultTable.getData() == MOCK_USING_STATEMENTS_COL);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_1);
}

TEST_CASE("UsesAbstraction - getAbstractions - Uses(Wildcard, Synonym)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockAllUsedVariables = MOCK_USED_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    UsesAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.getData() == MOCK_USED_VECTORS_COL_2);
    REQUIRE(resultTable.getColNames().size() == 1);
    REQUIRE(resultTable.getColNames().at(0) == MOCK_SYNONYM_VALUE_2);
}

TEST_CASE("UsesAbstraction - getAbstractions - Uses(Wildcard, Wildcard)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockAllUsedVariables = MOCK_USED_PAIRS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    UsesAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("UsesAbstraction - getAbstractions - Uses(WILDCARD, Ident)") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    mockReader.mockStatementsUsing = MOCK_USING_STATEMENTS;
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    UsesAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.isTableWildcard());
}

TEST_CASE("UsesAbstraction - getAbstractions - Uses(Wildcard, Wildcard)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    UsesAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.isTableWildcard() == false);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}

TEST_CASE("UsesAbstraction - getAbstractions - Uses(WILDCARD, Ident)_EMPTY") {
    MockPKBReader mockReader = MockPKBReader(MOCK_STORAGE);
    unique_ptr<IArgument> mockArgument1
            = ArgumentFactory::createArgument(MOCK_WILDCARD_VALUE);
    unique_ptr<IArgument> mockArgument2
            = ArgumentFactory::createArgument(MOCK_IDENT_VALUE_1);
    unique_ptr<AbstractionParams> abstractionParams
            = createMockAbstractionParams(mockReader, *mockArgument1,
                                          *mockArgument2, false);

    UsesAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();

    REQUIRE(resultTable.isTableWildcard() == false);
    REQUIRE(resultTable.isTableEmptyAndNotWildcard());
}
