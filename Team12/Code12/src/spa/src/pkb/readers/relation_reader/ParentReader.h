#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/Constants.h"
#include "pkb/interfaces/readers/IParentReader.h"
#include "pkb/storage/entity_storage/StmtStorage.h"
#include "pkb/storage/relation_storage/stmt_to_stmt/ParentStorage.h"

class ParentReader : public virtual IParentReader {
 private:
  ParentStorage& parent_storage_;
  StmtStorage& statement_storage_;

 protected:
  explicit ParentReader(ParentStorage& parent_storage,
                        StmtStorage& statement_storage)
      : parent_storage_(parent_storage),
        statement_storage_(statement_storage) {}

 public:
  std::vector<std::pair<std::string, std::string>> getImmediateChildrenOf(
      int statementNumber, StmtType statementType) override;

  std::pair<std::string, std::string> getImmediateParentOf(
      int statementNumber, StmtType statementType) override;

  bool isParent(int statementNumber, int childStatement) override;

  std::vector<std::pair<std::string, std::string>> getParentChildPairs(
      StmtType parentType, StmtType childType) override;

  std::vector<std::pair<std::string, std::string>> getChildrenStarOf(
      int statementNumber, StmtType statementType) override;

  std::vector<std::pair<std::string, std::string>> getParentStarOf(
      int statementNumber, StmtType statementType) override;

  bool isParentStar(int statementNumber, int childStatement) override;

  std::vector<std::pair<std::string, std::string>> getParentChildStarPairs(
      StmtType parentType, StmtType childType) override;
};
