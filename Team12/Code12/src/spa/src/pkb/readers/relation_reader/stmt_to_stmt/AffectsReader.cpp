#include "AffectsReader.h"

#include <cassert>

std::vector<std::pair<std::string, std::string>>
AffectsReader::getAffectsPairs() {
  std::vector<std::pair<std::string, std::string>> result;

  const auto assignStmts = stmtStore.getAllStmtsOf(StmtType::ASSIGN);

  for (const auto& assign : assignStmts) {
    std::unordered_set<std::string> done;
    std::string v = *modifiesSStore.getAllDirectSuccessorsOf(assign).begin();

    findAffectsPairs(assign, assign, v, done, result);
  }

  return result;
}

void AffectsReader::findAffectsPairs(
    int originalStmt, int currentStmt, const std::string& variable,
    std::unordered_set<std::string>& done,
    std::vector<std::pair<std::string, std::string>>& result) {
  done.insert(std::to_string(currentStmt));

  for (auto& nextStmt : nextStore.getAllDirectSuccessorsOf(currentStmt)) {
    if (nextStmt == originalStmt &&
        usesSStore.hasDirectRelation(nextStmt, variable)) {
      result.emplace_back(std::to_string(originalStmt),
                          std::to_string(nextStmt));
    }

    if (done.count(std::to_string(nextStmt)) > 0) {
      continue;
    }

    if (stmtStore.hasStmt(nextStmt, StmtType::ASSIGN) &&
        usesSStore.hasDirectRelation(nextStmt, variable)) {
      result.emplace_back(std::to_string(originalStmt),
                          std::to_string(nextStmt));
    }

    if (modifiesSStore.hasDirectRelation(nextStmt, variable)) {
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
    if (pair.first == firstStmtStr && pair.second == secondStmtStr) {
      return true;
    }
  }

  return false;
}

std::vector<std::string> AffectsReader::getAffects(int firstStmtNum,
                                                   StmtType stmtType) {
  assert(stmtType == StmtType::ASSIGN || stmtType == StmtType::STMT);
  std::vector<std::string> result;

  const auto affectsPairs = getAffectsPairs();
  std::string firstStmtStr = std::to_string(firstStmtNum);

  for (const auto& pair : affectsPairs) {
    if (pair.first == firstStmtStr) {
      result.push_back(pair.second);
    }
  }

  return result;
}

std::vector<std::string> AffectsReader::getAffectedBy(int secondStmtNum,
                                                      StmtType stmtType) {
  assert(stmtType == StmtType::ASSIGN || stmtType == StmtType::STMT);
  std::vector<std::string> result;

  const auto affectsPairs = getAffectsPairs();
  std::string secondStmtStr = std::to_string(secondStmtNum);

  for (const auto& pair : affectsPairs) {
    if (pair.second == secondStmtStr) {
      result.push_back(pair.first);
    }
  }

  return result;
}
