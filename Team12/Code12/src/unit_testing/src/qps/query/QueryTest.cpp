//#include <catch.hpp>
//#include "qps/query/Query.h"
//#include "../mocks/MockPKBReader.h"
//#include "../abstraction/FollowsAbstraction/FollowsAbstractionTestData.h"
//#include "qps/clause/suchThatClause/SuchThatClause.h"
//
// TEST_CASE("Query - getAbstractions - Follows(Synonym, Wildcard)") {
//    PKBStorage mockStorage = PKBStorage();
//    MockPKBReader mockPkbReader = MockPKBReader(mockStorage);
//    mockPkbReader.mockFollowsPairs = MOCK_FOLLOWS_PAIRS;
//    unique_ptr<AbstractArgument> mockArgument1 =
//    ArgumentFactory::createArgument("x"); unique_ptr<AbstractArgument>
//    mockArgument2 = ArgumentFactory::createArgument("y"); unique_ptr<Context>
//    mockContext = std::make_unique<Context>(); mockContext->addSynonym("x",
//    "assign"); mockContext->addSynonym("y", "assign");
//    unique_ptr<SuchThatClause> suchThatClause =
//    std::make_unique<SuchThatClause>(
//            FOLLOWS_ENUM,
//            std::move(mockArgument1),
//            std::move(mockArgument2),
//            false);
//
//    Query query(mockPkbReader);
//    query.addClause(std::move(suchThatClause))
//
//}
//
