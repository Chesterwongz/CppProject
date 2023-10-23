#pragma once

#include <cassert>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/Constants.h"
#include "common/StmtTypes.h"
#include "common/utils/CollectionUtils.h"
#include "pkb/interfaces/readers/IFollowsReader.h"
#include "pkb/storage/FollowsStore.h"
#include "pkb/storage/StmtStore.h"

class FollowsReader : public IFollowsReader {
 private:
  FollowsStore& followsStore;
  StmtStore& stmtStore;

 protected:
  explicit FollowsReader(FollowsStore& storage, StmtStore& stmtStorage)
      : followsStore(storage), stmtStore(stmtStorage) {}

 public:
  std::vector<std::string> getFollowing(int stmt, StmtType stmtType) override;

  std::vector<std::string> getFollowed(int stmt, StmtType stmtType) override;

  bool isFollows(int stmt1, int stmt2) override;

  std::vector<std::pair<std::string, std::string>> getFollowsPairs(
      StmtType stmtType1, StmtType stmtType2) override;

  // ================================ FollowsT ================================

  std::vector<std::string> getFollowsStar(int stmt, StmtType stmtType) override;

  std::vector<std::string> getFollowedStar(int stmt,
                                           StmtType stmtType) override;

  bool isFollowsStar(int stmt1, int stmt2) override;

  std::vector<std::pair<std::string, std::string>> getFollowsStarPairs(
      StmtType stmtType1, StmtType stmtType2) override;
};
