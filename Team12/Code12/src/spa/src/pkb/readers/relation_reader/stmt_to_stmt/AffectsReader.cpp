#include "AffectsReader.h"

std::vector<std::pair<std::string, std::string>>
AffectsReader::getAffectsPairs() {
  std::vector<std::pair<std::string, std::string>> result;

  const auto assignStmts = stmtStore.getAllStmtsOf(StmtType::ASSIGN);

  for (const auto& assign : assignStmts) {
    if (!modifiesSStore.hasDirectSuccessors(assign)) continue;
    std::unordered_set<std::string> done;
    std::string v = *modifiesSStore.getDirectSuccessors(assign).begin();

    findAffectsPairs(assign, assign, v, done, result);
  }

  return result;
}

void AffectsReader::findAffectsPairs(
    int originalStmt, int currentStmt, const std::string& variable,
    std::unordered_set<std::string>& done,
    std::vector<std::pair<std::string, std::string>>& result) {
  done.insert(std::to_string(currentStmt));
  if (!nextStore.hasDirectSuccessors(currentStmt)) return;
  for (const auto& nextStmt : nextStore.getDirectSuccessors(currentStmt)) {
    if (nextStmt == originalStmt &&
        usesSStore.hasDirectRelation(nextStmt, variable)) {
      result.emplace_back(std::to_string(originalStmt),
                          std::to_string(nextStmt));
    }

    if (done.count(std::to_string(nextStmt))) {
      continue;
    }

    if (stmtStore.hasStmt(nextStmt, StmtType::ASSIGN) &&
        usesSStore.hasDirectRelation(nextStmt, variable)) {
      result.emplace_back(std::to_string(originalStmt),
                          std::to_string(nextStmt));
    }

    bool isValidType = stmtStore.hasStmt(nextStmt, StmtType::ASSIGN) ||
                       stmtStore.hasStmt(nextStmt, StmtType::READ) ||
                       stmtStore.hasStmt(nextStmt, StmtType::CALL);

    if (isValidType && modifiesSStore.hasDirectRelation(nextStmt, variable)) {
      continue;
    }

    findAffectsPairs(originalStmt, nextStmt, variable, done, result);
  }
}

bool AffectsReader::isAffects(int firstStmtNum, int secondStmtNum) {
  std::vector<std::pair<std::string, std::string>> affectsPairs =
      getAffectsPairs();
  std::string firstStmtStr = std::to_string(firstStmtNum);
  std::string secondStmtStr = std::to_string(secondStmtNum);

  for (const auto& pair : affectsPairs) {
    if ((firstStmtNum == common::WILDCARD_STMT_NUM &&
         pair.second == secondStmtStr) ||
        (pair.first == firstStmtStr &&
         secondStmtNum == common::WILDCARD_STMT_NUM) ||
        (pair.first == firstStmtStr && pair.second == secondStmtStr)) {
      return true;
    }
  }

  return false;
}

std::vector<std::string> AffectsReader::getAffects(int s1, StmtType type2) {
  std::vector<std::string> result;

  const auto affectsPairs = getAffectsPairs();
  std::string firstStmtStr = std::to_string(s1);

  for (const auto& pair : affectsPairs) {
    if (s1 == common::WILDCARD_STMT_NUM || pair.first == firstStmtStr) {
      result.push_back(pair.second);
    }
  }

  return result;
}

std::vector<std::string> AffectsReader::getAffectedBy(int s2, StmtType type1) {
  std::vector<std::string> result;

  const auto affectsPairs = getAffectsPairs();
  std::string secondStmtStr = std::to_string(s2);

  for (const auto& pair : affectsPairs) {
    if (s2 == common::WILDCARD_STMT_NUM || pair.second == secondStmtStr) {
      result.push_back(pair.first);
    }
  }

  return result;
}

bool AffectsReader::hasAffects() {
  std::vector<std::pair<std::string, std::string>> result;

  const auto assignStmts = stmtStore.getAllStmtsOf(StmtType::ASSIGN);

  for (const auto& assign : assignStmts) {
    if (!modifiesSStore.hasDirectSuccessors(assign)) continue;
    std::unordered_set<std::string> done;
    std::string v = *modifiesSStore.getDirectSuccessors(assign).begin();

    findAffectsPairs(assign, assign, v, done, result);
    if (!result.empty()) {
      return true;
    }
  }

  return !result.empty();
}
