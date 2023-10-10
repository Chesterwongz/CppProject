#include "FollowsReader.h"

std::string FollowsReader::getFollowing(int statementNumber,
                                        StmtType statementType) {
  int followingStatement =
      follows_storage_.getImmediateFollows(statementNumber);
  if (followingStatement != -1 &&
      stmt_storage_.isStatementType(followingStatement, statementType)) {
    return std::to_string(followingStatement);
  }

  return std::to_string(-1);
}

std::string FollowsReader::getFollowed(int statementNumber,
                                       StmtType statementType) {
  int followedStatement =
      follows_storage_.getImmediateFollowedBy(statementNumber);
  if (followedStatement != -1 &&
      stmt_storage_.isStatementType(followedStatement, statementType)) {
    return std::to_string(followedStatement);
  }

  return std::to_string(-1);
}

bool FollowsReader::isFollows(int statementNumber, int followingStatement) {
  int followsStmt = follows_storage_.getImmediateFollows(statementNumber);
  return followsStmt == followingStatement;
}

std::vector<std::pair<std::string, std::string>> FollowsReader::getFollowsPairs(
    StmtType statementType1, StmtType statementType2) {
  std::set<int> firstStatementList =
      stmt_storage_.getStatementNumbersFromStatementType(statementType1);
  std::set<int> secondStatementList =
      stmt_storage_.getStatementNumbersFromStatementType(statementType2);

  std::vector<std::pair<std::string, std::string>> followsPairs;

  for (int firstStatement : firstStatementList) {
    int followsResult = follows_storage_.getImmediateFollows(firstStatement);
    if (followsResult != -1 && secondStatementList.count(followsResult)) {
      followsPairs.emplace_back(std::to_string(firstStatement),
                                std::to_string(followsResult));
    }
  }

  return followsPairs;
}

std::vector<std::pair<std::string, std::string>> FollowsReader::getFollowsStar(
    int statementNumber, StmtType statementType) {
  std::set<int> allFollowsStar =
      follows_storage_.getAllFollows(statementNumber);

  std::set<int> allMatchingStatements =
      stmt_storage_.getStatementNumbersFromStatementType(statementType);

  std::vector<std::pair<std::string, std::string>> result;

  for (int stmt : allFollowsStar) {
    if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
      result.emplace_back(std::to_string(statementNumber),
                          std::to_string(stmt));
    }
  }

  return result;
}

std::vector<std::pair<std::string, std::string>> FollowsReader::getFollowedStar(
    int statementNumber, StmtType statementType) {
  std::set<int> allFollowedStar =
      follows_storage_.getAllFollowedBy(statementNumber);

  std::set<int> allMatchingStatements =
      stmt_storage_.getStatementNumbersFromStatementType(statementType);

  std::vector<std::pair<std::string, std::string>> result;

  for (int stmt : allFollowedStar) {
    if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
      result.emplace_back(std::to_string(stmt),
                          std::to_string(statementNumber));
    }
  }

  return result;
}

bool FollowsReader::isFollowsStar(int statementNumber, int followingStatement) {
  std::set<int> allFollowsStar =
      follows_storage_.getAllFollows(statementNumber);
  return allFollowsStar.find(followingStatement) != allFollowsStar.end();
}

// TODO(Chester): S1 (Major): DRY Violation (multiple instances). There are
//  method implementation structures that have been
// repeated.
std::vector<std::pair<std::string, std::string>>
FollowsReader::getFollowsStarPairs(StmtType statementType1,
                                   StmtType statementType2) {
  std::set<int> firstStatementList =
      stmt_storage_.getStatementNumbersFromStatementType(statementType1);
  std::set<int> secondStatementList =
      stmt_storage_.getStatementNumbersFromStatementType(statementType2);

  std::vector<std::pair<std::string, std::string>> followsPairs;

  for (int firstStatement : firstStatementList) {
    std::set<int> followsResult =
        follows_storage_.getAllFollows(firstStatement);
    for (int follows : followsResult) {
      if (secondStatementList.count(follows)) {
        followsPairs.emplace_back(std::to_string(firstStatement),
                                  std::to_string(follows));
      }
    }
  }

  return followsPairs;
}
