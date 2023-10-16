#include <catch.hpp>
#include <unordered_set>

#include "pkb/facade/PKBReader.h"
#include "pkb/facade/PKBWriter.h"
#include "pkb/readers/relation_reader/stmt_to_stmt/AffectsReader.h"

// TEST_CASE("AffectsReader Tests 1") {
//   CallsStorage callsStorage;
//   ModifiesStorage modifiesStorage;
//   NextStorage nextStorage;
//   StmtStorage stmtStorage;
//   UsesStorage usesStorage;
//
//   stmtStorage.setStatement(1, StmtType::ASSIGN);
//   stmtStorage.setStatement(2, StmtType::ASSIGN);
//   stmtStorage.setStatement(3, StmtType::WHILE);
//   stmtStorage.setStatement(4, StmtType::ASSIGN);
//   stmtStorage.setStatement(5, StmtType::CALL);
//   stmtStorage.setStatement(6, StmtType::ASSIGN);
//   stmtStorage.setStatement(7, StmtType::IF);
//   stmtStorage.setStatement(8, StmtType::ASSIGN);
//   stmtStorage.setStatement(9, StmtType::ASSIGN);
//   stmtStorage.setStatement(10, StmtType::ASSIGN);
//   stmtStorage.setStatement(11, StmtType::ASSIGN);
//   stmtStorage.setStatement(12, StmtType::ASSIGN);
//
//   modifiesStorage.addModifies("x", 1);
//   modifiesStorage.addModifies("i", 2);
//   modifiesStorage.addModifies("x", 4);
//   modifiesStorage.addModifies("i", 6);
//   modifiesStorage.addModifies("x", 8);
//   modifiesStorage.addModifies("z", 9);
//   modifiesStorage.addModifies("z", 10);
//   modifiesStorage.addModifies("y", 11);
//   modifiesStorage.addModifies("x", 12);
//   modifiesStorage.addModifies("z", "Third");
//   modifiesStorage.addModifies("v", "Third");
//
//   usesStorage.addUses("x", 4);
//   usesStorage.addUses("y", 4);
//   usesStorage.addUses("i", 6);
//   usesStorage.addUses("x", 8);
//   usesStorage.addUses("z", 10);
//   usesStorage.addUses("x", 10);
//   usesStorage.addUses("i", 10);
//   usesStorage.addUses("z", 11);
//   usesStorage.addUses("x", 12);
//   usesStorage.addUses("y", 12);
//   usesStorage.addUses("z", 12);
//
//   callsStorage.setCallsRelationship("Second", "Third", 5);
//
//   nextStorage.addNext(1, 2);
//   nextStorage.addNext(2, 3);
//   nextStorage.addNext(3, 4);
//   nextStorage.addNext(3, 7);
//   nextStorage.addNext(4, 5);
//   nextStorage.addNext(5, 6);
//   nextStorage.addNext(6, 3);
//   nextStorage.addNext(6, 7);
//   nextStorage.addNext(7, 8);
//   nextStorage.addNext(7, 9);
//   nextStorage.addNext(8, 10);
//   nextStorage.addNext(9, 10);
//   nextStorage.addNext(10, 11);
//   nextStorage.addNext(11, 12);
//
//   SECTION("AffectsPairs") {
//     AffectsReader affectsReader(callsStorage, modifiesStorage, nextStorage,
//                                 stmtStorage, usesStorage);
//     std::vector<std::pair<std::string, std::string>> result =
//         affectsReader.getAffectsPairs();
//     REQUIRE(result ==
//             std::vector<std::pair<std::string, std::string>> {{"2", "6"},
//                                                               {"4", "8"},
//                                                               {"4", "10"},
//                                                               {"6", "6"},
//                                                               {"1", "4"},
//                                                               {"1", "8"},
//                                                               {"1", "10"},
//                                                               {"1", "12"},
//                                                               {"2", "10"},
//                                                               {"9", "10"}});
//   }
// }

 TEST_CASE("AffectsReader Tests 2") {
   CallsStorage callsStorage;
   ModifiesStorage modifiesStorage;
   NextStorage nextStorage;
   StmtStorage stmtStorage;
   UsesStorage usesStorage;

   stmtStorage.setStatement(1, StmtType::ASSIGN);
   stmtStorage.setStatement(2, StmtType::IF);
   stmtStorage.setStatement(3, StmtType::ASSIGN);
   stmtStorage.setStatement(4, StmtType::ASSIGN);
   stmtStorage.setStatement(5, StmtType::ASSIGN);

   modifiesStorage.addModifies("x", 1);
   modifiesStorage.addModifies("x", 3);
   modifiesStorage.addModifies("a", 4);
   modifiesStorage.addModifies("a", 5);

   usesStorage.addUses("a", 3);
   usesStorage.addUses("b", 4);
   usesStorage.addUses("x", 5);

   nextStorage.addNext(1, 2);
   nextStorage.addNext(2, 3);
   nextStorage.addNext(2, 4);
   nextStorage.addNext(3, 5);
   nextStorage.addNext(4, 5);

   SECTION("AffectsPairs") {
     AffectsReader affectsReader(callsStorage, modifiesStorage, nextStorage,
                                 stmtStorage, usesStorage);
     std::vector<std::pair<std::string, std::string>> result =
         affectsReader.getAffectsPairs();
     REQUIRE(result == std::vector<std::pair<std::string, std::string>> {
                           {"1", "5"}, {"3", "5"}});
   }
 }

 TEST_CASE("AffectsReader Tests 3") {
   CallsStorage callsStorage;
   ModifiesStorage modifiesStorage;
   NextStorage nextStorage;
   StmtStorage stmtStorage;
   UsesStorage usesStorage;

   stmtStorage.setStatement(1, StmtType::ASSIGN);
   stmtStorage.setStatement(2, StmtType::CALL);
   stmtStorage.setStatement(3, StmtType::ASSIGN);

   modifiesStorage.addModifies("x", 1);
   modifiesStorage.addModifies("v", 3);
   //modifiesStorage.addModifies("x", "q");

   usesStorage.addUses("a", 1);
   usesStorage.addUses("x", 3);

   nextStorage.addNext(1, 2);
   nextStorage.addNext(2, 3);

   callsStorage.setCallsRelationship("p", "q", 2);

   SECTION("AffectsPairs") {
     AffectsReader affectsReader(callsStorage, modifiesStorage, nextStorage,
                                 stmtStorage, usesStorage);
     std::vector<std::pair<std::string, std::string>> result =
         affectsReader.getAffectsPairs();
     REQUIRE(result == std::vector<std::pair<std::string, std::string>> {
                           {"1", "3"}});
   }
 }

TEST_CASE("AffectsReader Tests 4") {
  CallsStorage callsStorage;
  ModifiesStorage modifiesStorage;
  NextStorage nextStorage;
  StmtStorage stmtStorage;
  UsesStorage usesStorage;

  stmtStorage.setStatement(1, StmtType::ASSIGN);
  stmtStorage.setStatement(2, StmtType::ASSIGN);
  stmtStorage.setStatement(3, StmtType::ASSIGN);
  stmtStorage.setStatement(4, StmtType::CALL);
  stmtStorage.setStatement(5, StmtType::ASSIGN);
  stmtStorage.setStatement(6, StmtType::ASSIGN);
  stmtStorage.setStatement(7, StmtType::ASSIGN);
  stmtStorage.setStatement(8, StmtType::IF);
  stmtStorage.setStatement(9, StmtType::ASSIGN);
  stmtStorage.setStatement(10, StmtType::ASSIGN);
  stmtStorage.setStatement(11, StmtType::ASSIGN);

  modifiesStorage.addModifies("x", 1);
  modifiesStorage.addModifies("y", 2);
  modifiesStorage.addModifies("z", 3);
  modifiesStorage.addModifies("z", 5);
  modifiesStorage.addModifies("x", 6);
  modifiesStorage.addModifies("t", 7);
  modifiesStorage.addModifies("t", 9);
  modifiesStorage.addModifies("y", 10);
  modifiesStorage.addModifies("x", 11);
  modifiesStorage.addModifies("x", "q");
  modifiesStorage.addModifies("t", "q");
  modifiesStorage.addModifies("y", "q");

  usesStorage.addUses("y", 3);
  usesStorage.addUses("x", 5);
  usesStorage.addUses("y", 5);
  usesStorage.addUses("z", 5);
  usesStorage.addUses("x", 9);
  usesStorage.addUses("x", 10);
  usesStorage.addUses("z", 10);
  usesStorage.addUses("t", 11);
  usesStorage.addUses("x", "q");
  usesStorage.addUses("x", "q");
  usesStorage.addUses("z", "q");
  usesStorage.addUses("t", "q");

  nextStorage.addNext(1, 2);
  nextStorage.addNext(2, 3);
  nextStorage.addNext(3, 4);
  nextStorage.addNext(4, 5);
  nextStorage.addNext(6, 7);
  nextStorage.addNext(7, 8);
  nextStorage.addNext(8, 9);
  nextStorage.addNext(8, 10);
  nextStorage.addNext(9, 11);
  nextStorage.addNext(10, 11);

  callsStorage.setCallsRelationship("p", "q", 4);

  SECTION("AffectsPairs") {
    AffectsReader affectsReader(callsStorage, modifiesStorage, nextStorage,
                                stmtStorage, usesStorage);
    std::vector<std::pair<std::string, std::string>> result =
        affectsReader.getAffectsPairs();
    REQUIRE(result ==
            std::vector<std::pair<std::string, std::string>> {{"2", "3"},
                                                              {"3", "5"},
                                                              {"6", "9"},
                                                              {"6", "10"},
                                                              {"7", "11"},
                                                              {"9", "11"}});
  }
}