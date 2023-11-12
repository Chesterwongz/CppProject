#pragma once

#include <string>
#include <utility>
#include <vector>

#include "StmtToStmtReader.h"
#include "common/utils/CollectionUtils.h"
#include "pkb/interfaces/readers/IFollowsReader.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/relation_storage/RelationTStore.h"

class FollowsReader : public IFollowsReader {
 private:
  StmtToStmtReader reader;

 protected:
  explicit FollowsReader(RelationTStore<int>& store, StmtStore& stmtStorage)
      : reader(store, stmtStorage) {}

 public:
  std::vector<std::string> getFollowing(StmtType stmtType, int stmt) override;

  std::vector<std::string> getFollowed(StmtType stmtType, int stmt) override;

  bool isFollows(int stmt1, int stmt2) override;

  std::vector<std::pair<std::string, std::string>> getFollowsPairs(
      StmtType stmtType1, StmtType stmtType2) override;

  // ================================ FollowsT ================================

  std::vector<std::string> getFollowsStar(StmtType stmtType, int stmt) override;

  std::vector<std::string> getFollowedStar(StmtType stmtType, int stmt) override;

  bool isFollowsStar(int stmt1, int stmt2) override;

  std::vector<std::pair<std::string, std::string>> getFollowsStarPairs(
      StmtType stmtType1, StmtType stmtType2) override;
};
