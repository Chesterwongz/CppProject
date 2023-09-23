#include "catch.hpp"
#include "qps/abstraction/FollowsAbstraction/FollowsAbstraction.h"
#include "../../mocks/MockPKBReader.h"
#include "../../mocks/MockPKBReaderData.h"
#include "../../intermediateTable/IntermediateTableTestUtils.h"

TEST_CASE("FollowsAbstraction - getAbstractions - Follows(Synonym, Synonym") {
    PKBStorage storage{};
    MockPKBReader mockReader = MockPKBReader(storage);
    mockReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
    Context MOCK_CONTEXT = Context();
    unique_ptr<IArgument> MOCK_SYNONYM_ARG_1 = getMockSynonymArgument();
    unique_ptr<IArgument> MOCK_SYNONYM_ARG_2 = getMockSynonymArgument();
    MOCK_CONTEXT.addToken(MOCK_SYNONYM_NAME, "assign");
    unique_ptr<AbstractionParams> abstractionParams
        = std::make_unique<AbstractionParams>(
            mockReader,
            MOCK_CONTEXT,
            FOLLOWS,
            *MOCK_SYNONYM_ARG_1,
            *MOCK_SYNONYM_ARG_2,
            false);
    FollowsAbstraction abstraction(std::move(abstractionParams));
    IntermediateTable resultTable = abstraction.getAbstractions();
    resultTable.printTable();

    REQUIRE(isVectorsSameAsPairs(
            resultTable.getData(),
            MOCK_FOLLOWS_PAIRS));
}

//TEST_CASE("FollowsAbstraction - getAbstractions - Follows(Synonym, Wildcard") {
//
//}
//
//TEST_CASE("FollowsAbstraction - getAbstractions - Follows(Wildcard, Synonym") {
//
//}
//
//TEST_CASE("FollowsAbstraction - getAbstractions - Follows(Wildcard, Wildcard") {
//
//}
