#pragma once

#include <string>
#include <utility>
#include <vector>

#include "common/Constants.h"
#include "common/StmtTypes.h"
#include "common/utils/CollectionUtils.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/relation_storage/RelationStore.h"

class StmtToStmtDirectReader {
 private:
  RelationStore<int, int>& relationStore;
  StmtStore& stmtStore;

 protected:
  explicit StmtToStmtDirectReader(RelationStore<int, int>& relationStore,
                                  StmtStore& stmtStore)
      : relationStore(relationStore), stmtStore(stmtStore) {}

 public:
  std::vector<std::string> getDirectS1ByS2(int stmt2, StmtType stmtType1);

  std::vector<std::string> getDirectS2ByS1(int stmt1, StmtType stmtType2);

  bool hasDirectRelation(int stmt1, int stmt2);

  std::vector<std::pair<std::string, std::string>> getDirectS1AndS2Pairs(
      StmtType stmtType1, StmtType stmtType2);

  // ================================ FollowsT ================================

  std::vector<std::string> getFollowsStar(int stmt, StmtType stmtType);

  std::vector<std::string> getFollowedStar(int stmt, StmtType stmtType);

  bool isFollowsStar(int stmt1, int stmt2);

  std::vector<std::pair<std::string, std::string>> getFollowsStarPairs(
      StmtType stmtType1, StmtType stmtType2);
};
