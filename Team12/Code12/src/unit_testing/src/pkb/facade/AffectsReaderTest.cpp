#include <catch.hpp>
#include <unordered_set>

#include "../../common/utils/HelperFunctions.h"
#include "pkb/facade/PKBReader.h"
#include "pkb/facade/PKBWriter.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/AffectsReader.h"

TEST_CASE("AffectsReader Tests 1") {
  /*PKBStore store;
  PKBWriter writer(store);
  PKBReader reader(store);*/
  CallsStore callsStore;
  CallsSStore callsSStore;
  ModifiesPStore modifiesPStore;
  ModifiesSStore modifiesSStore;
  NextStore nextStore;
  StmtStore stmtStore;
  UsesSStore usesSStore;

  stmtStore.addStmt(1, StmtType::ASSIGN);
  stmtStore.addStmt(2, StmtType::ASSIGN);
  stmtStore.addStmt(3, StmtType::WHILE);
  stmtStore.addStmt(4, StmtType::ASSIGN);
  stmtStore.addStmt(5, StmtType::CALL);
  stmtStore.addStmt(6, StmtType::ASSIGN);
  stmtStore.addStmt(7, StmtType::IF);
  stmtStore.addStmt(8, StmtType::ASSIGN);
  stmtStore.addStmt(9, StmtType::ASSIGN);
  stmtStore.addStmt(10, StmtType::ASSIGN);
  stmtStore.addStmt(11, StmtType::ASSIGN);
  stmtStore.addStmt(12, StmtType::ASSIGN);

  modifiesSStore.addRelation(1, "x");
  modifiesSStore.addRelation(2, "i");
  modifiesSStore.addRelation(4, "x");
  modifiesSStore.addRelation(6, "i");
  modifiesSStore.addRelation(8, "x");
  modifiesSStore.addRelation(9, "z");
  modifiesSStore.addRelation(10, "z");
  modifiesSStore.addRelation(11, "y");
  modifiesSStore.addRelation(12, "x");
  modifiesSStore.addRelation(5, "z");
  modifiesSStore.addRelation(5, "v");
  modifiesPStore.addRelation("Third", "z");
  modifiesPStore.addRelation("Third", "v");

  usesSStore.addRelation(4, "x");
  usesSStore.addRelation(4, "y");
  usesSStore.addRelation(6, "i");
  usesSStore.addRelation(8, "x");
  usesSStore.addRelation(10, "i");
  usesSStore.addRelation(10, "x");
  usesSStore.addRelation(10, "z");
  usesSStore.addRelation(11, "z");
  usesSStore.addRelation(12, "x");
  usesSStore.addRelation(12, "y");
  usesSStore.addRelation(12, "z");

  callsStore.addRelation("Second", "Third");
  callsSStore.addRelation(5, "Third");

  nextStore.addRelation(1, 2);
  nextStore.addRelation(2, 3);
  nextStore.addRelation(3, 4);
  nextStore.addRelation(3, 7);
  nextStore.addRelation(4, 5);
  nextStore.addRelation(5, 6);
  nextStore.addRelation(6, 3);
  nextStore.addRelation(6, 7);
  nextStore.addRelation(7, 8);
  nextStore.addRelation(7, 9);
  nextStore.addRelation(8, 10);
  nextStore.addRelation(9, 10);
  nextStore.addRelation(10, 11);
  nextStore.addRelation(11, 12);

  SECTION("AffectsPairs") {
    AffectsReader affectsReader(callsStore, modifiesPStore, modifiesSStore,
                                nextStore, stmtStore, usesSStore);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(compareVectorContents(
        result,
        std::vector<std::pair<std::string, std::string>> {{"1", "4"},
                                                          {"1", "8"},
                                                          {"1", "10"},
                                                          {"1", "12"},
                                                          {"2", "6"},
                                                          {"2", "10"},
                                                          {"4", "4"},
                                                          {"4", "8"},
                                                          {"4", "10"},
                                                          {"4", "12"},
                                                          {"6", "6"},
                                                          {"6", "10"},
                                                          {"8", "10"},
                                                          {"8", "12"},
                                                          {"9", "10"},
                                                          {"10", "11"},
                                                          {"10", "12"},
                                                          {"11", "12"}}));
  }
}

// TEST_CASE("AffectsReader Tests 2 - Code 7") {
//   CallsStorage callsStorage;
//   ModifiesStorage modifiesStorage;
//   NextStorage nextStorage;
//   StmtStorage stmtStorage;
//   UsesStorage usesStorage;
//
//   stmtStorage.setStatement(1, StmtType::ASSIGN);
//   stmtStorage.setStatement(2, StmtType::IF);
//   stmtStorage.setStatement(3, StmtType::ASSIGN);
//   stmtStorage.setStatement(4, StmtType::ASSIGN);
//   stmtStorage.setStatement(5, StmtType::ASSIGN);
//
//   modifiesStorage.addModifies("x", 1);
//   modifiesStorage.addModifies("x", 3);
//   modifiesStorage.addModifies("a", 4);
//   modifiesStorage.addModifies("a", 5);
//
//   usesStorage.addUses("a", 3);
//   usesStorage.addUses("b", 4);
//   usesStorage.addUses("x", 5);
//
//   nextStore.addRelation(1, 2);
//   nextStore.addRelation(2, 3);
//   nextStore.addRelation(2, 4);
//   nextStore.addRelation(3, 5);
//   nextStore.addRelation(4, 5);
//
//   SECTION("AffectsPairs") {
//     AffectsReader affectsReader(callsStorage, modifiesStorage, nextStorage,
//                                 stmtStorage, usesStorage);
//     std::vector<std::pair<std::string, std::string>> result =
//         affectsReader.getAffectsPairs();
//     REQUIRE(result == std::vector<std::pair<std::string, std::string>> {
//                           {"1", "5"}, {"3", "5"}});
//   }
// }
//
// TEST_CASE("AffectsReader Tests 3 - Code 8") {
//   CallsStorage callsStorage;
//   ModifiesStorage modifiesStorage;
//   NextStorage nextStorage;
//   StmtStorage stmtStorage;
//   UsesStorage usesStorage;
//
//   stmtStorage.setStatement(1, StmtType::ASSIGN);
//   stmtStorage.setStatement(2, StmtType::CALL);
//   stmtStorage.setStatement(3, StmtType::ASSIGN);
//
//   modifiesStorage.addModifies("x", 1);
//   modifiesStorage.addModifies("v", 3);
//   // If Modifies("q", "x") does not hold, then Affects(1, 3) holds.
//   // modifiesStorage.addModifies("x", "q");
//
//   usesStorage.addUses("a", 1);
//   usesStorage.addUses("x", 3);
//
//   nextStore.addRelation(1, 2);
//   nextStore.addRelation(2, 3);
//
//   callsStorage.setCallsRelationship("p", "q", 2);
//
//   SECTION("AffectsPairs") {
//     AffectsReader affectsReader(callsStorage, modifiesStorage, nextStorage,
//                                 stmtStorage, usesStorage);
//     std::vector<std::pair<std::string, std::string>> result =
//         affectsReader.getAffectsPairs();
//     REQUIRE(result ==
//             std::vector<std::pair<std::string, std::string>> {{"1", "3"}});
//   }
// }
//
// TEST_CASE("AffectsReader Tests 4 - Code 9") {
//   CallsStorage callsStorage;
//   ModifiesStorage modifiesStorage;
//   NextStorage nextStorage;
//   StmtStorage stmtStorage;
//   UsesStorage usesStorage;
//
//   stmtStorage.setStatement(1, StmtType::ASSIGN);
//   stmtStorage.setStatement(2, StmtType::ASSIGN);
//   stmtStorage.setStatement(3, StmtType::ASSIGN);
//   stmtStorage.setStatement(4, StmtType::CALL);
//   stmtStorage.setStatement(5, StmtType::ASSIGN);
//   stmtStorage.setStatement(6, StmtType::ASSIGN);
//   stmtStorage.setStatement(7, StmtType::ASSIGN);
//   stmtStorage.setStatement(8, StmtType::IF);
//   stmtStorage.setStatement(9, StmtType::ASSIGN);
//   stmtStorage.setStatement(10, StmtType::ASSIGN);
//   stmtStorage.setStatement(11, StmtType::ASSIGN);
//
//   modifiesStorage.addModifies("x", 1);
//   modifiesStorage.addModifies("y", 2);
//   modifiesStorage.addModifies("z", 3);
//   modifiesStorage.addModifies("z", 5);
//   modifiesStorage.addModifies("x", 6);
//   modifiesStorage.addModifies("t", 7);
//   modifiesStorage.addModifies("t", 9);
//   modifiesStorage.addModifies("y", 10);
//   modifiesStorage.addModifies("x", 11);
//   modifiesStorage.addModifies("x", "q");
//   modifiesStorage.addModifies("t", "q");
//   modifiesStorage.addModifies("y", "q");
//
//   usesStorage.addUses("y", 3);
//   usesStorage.addUses("x", 5);
//   usesStorage.addUses("y", 5);
//   usesStorage.addUses("z", 5);
//   usesStorage.addUses("x", 9);
//   usesStorage.addUses("x", 10);
//   usesStorage.addUses("z", 10);
//   usesStorage.addUses("t", 11);
//   usesStorage.addUses("x", "q");
//   usesStorage.addUses("x", "q");
//   usesStorage.addUses("z", "q");
//   usesStorage.addUses("t", "q");
//
//   nextStore.addRelation(1, 2);
//   nextStore.addRelation(2, 3);
//   nextStore.addRelation(3, 4);
//   nextStore.addRelation(4, 5);
//   nextStore.addRelation(6, 7);
//   nextStore.addRelation(7, 8);
//   nextStore.addRelation(8, 9);
//   nextStore.addRelation(8, 10);
//   nextStore.addRelation(9, 11);
//   nextStore.addRelation(10, 11);
//
//   callsStorage.setCallsRelationship("p", "q", 4);
//
//   SECTION("AffectsPairs") {
//     AffectsReader affectsReader(callsStorage, modifiesStorage, nextStorage,
//                                 stmtStorage, usesStorage);
//     std::vector<std::pair<std::string, std::string>> result =
//         affectsReader.getAffectsPairs();
//     REQUIRE(result ==
//             std::vector<std::pair<std::string, std::string>> {{"2", "3"},
//                                                               {"3", "5"},
//                                                               {"6", "9"},
//                                                               {"6", "10"},
//                                                               {"7", "11"},
//                                                               {"9", "11"}});
//   }
// }
//
// TEST_CASE("AffectsReader Tests 5 - Code 11") {
//   CallsStorage callsStorage;
//   ModifiesStorage modifiesStorage;
//   NextStorage nextStorage;
//   StmtStorage stmtStorage;
//   UsesStorage usesStorage;
//
//   stmtStorage.setStatement(1, StmtType::ASSIGN);
//   stmtStorage.setStatement(2, StmtType::READ);
//   stmtStorage.setStatement(3, StmtType::ASSIGN);
//
//   modifiesStorage.addModifies("x", 1);
//   modifiesStorage.addModifies("x", 2);
//   modifiesStorage.addModifies("v", 3);
//
//   usesStorage.addUses("a", 1);
//   usesStorage.addUses("x", 3);
//
//   nextStore.addRelation(1, 2);
//   nextStore.addRelation(2, 3);
//
//   SECTION("AffectsPairs") {
//     AffectsReader affectsReader(callsStorage, modifiesStorage, nextStorage,
//                                 stmtStorage, usesStorage);
//     std::vector<std::pair<std::string, std::string>> result =
//         affectsReader.getAffectsPairs();
//     REQUIRE(result == std::vector<std::pair<std::string, std::string>> {});
//   }
// }
//
// TEST_CASE("AffectsReader Tests 6 - Code 10") {
//   CallsStorage callsStorage;
//   ModifiesStorage modifiesStorage;
//   NextStorage nextStorage;
//   StmtStorage stmtStorage;
//   UsesStorage usesStorage;
//
//   stmtStorage.setStatement(1, StmtType::ASSIGN);
//   stmtStorage.setStatement(2, StmtType::CALL);
//   stmtStorage.setStatement(3, StmtType::ASSIGN);
//   stmtStorage.setStatement(4, StmtType::IF);
//   stmtStorage.setStatement(5, StmtType::ASSIGN);
//   stmtStorage.setStatement(6, StmtType::ASSIGN);
//
//   modifiesStorage.addModifies("x", 1);
//   modifiesStorage.addModifies("a", 3);
//   modifiesStorage.addModifies("x", 5);
//   modifiesStorage.addModifies("a", 6);
//   modifiesStorage.addModifies("a", "beta");
//   modifiesStorage.addModifies("x", "beta");
//
//   usesStorage.addUses("x", 3);
//   usesStorage.addUses("a", 5);
//   usesStorage.addUses("b", 6);
//   usesStorage.addUses("a", "beta");
//   usesStorage.addUses("b", "beta");
//   usesStorage.addUses("i", "beta");
//
//   nextStore.addRelation(1, 2);
//   nextStore.addRelation(2, 3);
//   nextStore.addRelation(4, 5);
//   nextStore.addRelation(4, 6);
//
//   callsStorage.setCallsRelationship("alpha", "beta", 2);
//
//   SECTION("AffectsPairs") {
//     AffectsReader affectsReader(callsStorage, modifiesStorage, nextStorage,
//                                 stmtStorage, usesStorage);
//     std::vector<std::pair<std::string, std::string>> result =
//         affectsReader.getAffectsPairs();
//     REQUIRE(result == std::vector<std::pair<std::string, std::string>> {});
//   }
// }
