#include "ParentReader.h"

std::vector<std::pair<std::string, std::string>>
ParentReader::getImmediateChildrenOf(int statementNumber,
                                     StmtType statementType) {
  std::set<int> allImmediateChildren =
      parent_storage_.getImmediateChildren(statementNumber);

  std::set<int> allMatchingStatements =
      statement_storage_.getStatementNumbersFromStatementType(statementType);

  std::vector<std::pair<std::string, std::string>> result;

  for (int stmt : allImmediateChildren) {
    if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
      result.emplace_back(std::to_string(statementNumber),
                          std::to_string(stmt));
    }
  }

  return result;
}

std::pair<std::string, std::string> ParentReader::getImmediateParentOf(
    int statementNumber, StmtType statementType) {
  int immediateParent = parent_storage_.getImmediateParent(statementNumber);

  std::pair<std::string, std::string> result;

  if (immediateParent != common::INVALID_STMT_NUM &&
      statement_storage_.isStatementType(immediateParent, statementType)) {
    result = std::make_pair(std::to_string(immediateParent),
                            std::to_string(statementNumber));
  }

  return result;
}

bool ParentReader::isParent(int statementNumber, int childStatement) {
  std::set<int> allImmediateChildren =
      parent_storage_.getImmediateChildren(statementNumber);
  return allImmediateChildren.find(childStatement) !=
         allImmediateChildren.end();
}

std::vector<std::pair<std::string, std::string>>
ParentReader::getParentChildPairs(StmtType parentType, StmtType childType) {
  std::set<int> firstStatementList =
      statement_storage_.getStatementNumbersFromStatementType(parentType);
  std::set<int> secondStatementList =
      statement_storage_.getStatementNumbersFromStatementType(childType);

  std::vector<std::pair<std::string, std::string>> parentChildPairs;

  for (int firstStatement : firstStatementList) {
    std::set<int> allChildren =
        parent_storage_.getImmediateChildren(firstStatement);
    for (int child : allChildren) {
      if (secondStatementList.find(child) != secondStatementList.end()) {
        parentChildPairs.emplace_back(std::to_string(firstStatement),
                                      std::to_string(child));
      }
    }
  }
  return parentChildPairs;
}

std::vector<std::pair<std::string, std::string>>
ParentReader::getChildrenStarOf(int statementNumber, StmtType statementType) {
  std::set<int> allChildren = parent_storage_.getAllChildren(statementNumber);

  std::set<int> allMatchingStatements =
      statement_storage_.getStatementNumbersFromStatementType(statementType);

  std::vector<std::pair<std::string, std::string>> result;

  for (int stmt : allChildren) {
    if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
      result.emplace_back(std::to_string(statementNumber),
                          std::to_string(stmt));
    }
  }

  return result;
}

std::vector<std::pair<std::string, std::string>> ParentReader::getParentStarOf(
    int statementNumber, StmtType statementType) {
  std::set<int> allParents = parent_storage_.getAllParents(statementNumber);

  std::set<int> allMatchingStatements =
      statement_storage_.getStatementNumbersFromStatementType(statementType);

  std::vector<std::pair<std::string, std::string>> result;

  for (int stmt : allParents) {
    if (allMatchingStatements.find(stmt) != allMatchingStatements.end()) {
      result.emplace_back(std::to_string(stmt),
                          std::to_string(statementNumber));
    }
  }

  return result;
}

bool ParentReader::isParentStar(int statementNumber, int childStatement) {
  std::set<int> allChildren = parent_storage_.getAllChildren(statementNumber);
  return allChildren.find(childStatement) != allChildren.end();
}

std::vector<std::pair<std::string, std::string>>
ParentReader::getParentChildStarPairs(StmtType parentType, StmtType childType) {
  std::set<int> firstStatementList =
      statement_storage_.getStatementNumbersFromStatementType(parentType);
  std::set<int> secondStatementList =
      statement_storage_.getStatementNumbersFromStatementType(childType);

  std::vector<std::pair<std::string, std::string>> parentChildStarPairs;

  for (int firstStatement : firstStatementList) {
    std::set<int> allChildren = parent_storage_.getAllChildren(firstStatement);
    for (int child : allChildren) {
      if (secondStatementList.find(child) != secondStatementList.end()) {
        parentChildStarPairs.emplace_back(std::to_string(firstStatement),
                                          std::to_string(child));
      }
    }
  }
  return parentChildStarPairs;
}
