#pragma once

#include <string>
#include <utility>
#include <vector>

#include "common/Constants.h"
#include "common/StmtTypes.h"
#include "common/utils/CollectionUtils.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/relation_storage/RelationTStore.h"

class StmtToStmtReader {
 private:
  RelationTStore<int>& store;
  StmtStore& stmtStore;

 public:
  explicit StmtToStmtReader(RelationTStore<int>& store, StmtStore& stmtStore)
      : store(store), stmtStore(stmtStore) {}

  std::vector<std::string> getDirectS1ByS2(int s2, StmtType stmtType1);

  std::vector<std::string> getDirectS2ByS1(int stmt1, StmtType stmtType2);

  bool hasDirectRelation(int stmt1, int stmt2);

  std::vector<std::pair<std::string, std::string>> getDirectS1AndS2Pairs(
      StmtType stmtType1, StmtType stmtType2);

  bool hasDirectS1AndS2Pairs();

  // ================================ FollowsT ================================

  std::vector<std::string> getTransitiveS1ByS2(int s2, StmtType stmtType1);

  std::vector<std::string> getTransitiveS2ByS1(int s1, StmtType stmtType2);

  bool hasTransitiveRelation(int s1, int s2);

  std::vector<std::pair<std::string, std::string>> getTransitiveS1AndS2Pairs(
      StmtType stmtType1, StmtType stmtType2);

  bool hasTransitiveS1AndS2Pairs();
};
