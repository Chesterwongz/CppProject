#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"
#include "pkb/interfaces/readers/IFollowsReader.h"
#include "pkb/storage/entity_storage/StmtStorage.h"
#include "pkb/storage/relation_storage/stmt_to_stmt/FollowsStorage.h"

class FollowsReader : public IFollowsReader {
 private:
  FollowsStorage& follows_storage_;
  StmtStorage& stmt_storage_;

 protected:
  explicit FollowsReader(FollowsStorage& storage, StmtStorage& stmtStorage)
      : follows_storage_(storage), stmt_storage_(stmtStorage) {}

 public:
  std::string getFollowing(int statementNumber,
                           StmtType statementType) override;

  std::string getFollowed(int statementNumber, StmtType statementType) override;

  bool isFollows(int statementNumber, int followingStatement) override;

  std::vector<std::pair<std::string, std::string>> getFollowsPairs(
      StmtType statementType1, StmtType statementType2) override;

  std::vector<std::pair<std::string, std::string>> getFollowsStar(
      int statementNumber, StmtType statementType) override;

  std::vector<std::pair<std::string, std::string>> getFollowedStar(
      int statementNumber, StmtType statementType) override;

  bool isFollowsStar(int statementNumber, int followingStatement) override;

  std::vector<std::pair<std::string, std::string>> getFollowsStarPairs(
      StmtType statementType1, StmtType statementType2) override;
};
