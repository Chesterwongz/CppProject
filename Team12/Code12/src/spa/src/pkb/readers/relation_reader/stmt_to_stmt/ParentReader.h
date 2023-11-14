#pragma once

#include <string>
#include <utility>
#include <vector>

#include "StmtToStmtReader.h"
#include "common/utils/CollectionUtils.h"
#include "pkb/interfaces/readers/IParentReader.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/relation_storage/RelationTStore.h"

class ParentReader : public IParentReader {
 private:
  StmtToStmtReader reader;

 protected:
  explicit ParentReader(RelationTStore<int>& parentStore, StmtStore& stmtStore)
      : reader(parentStore, stmtStore) {}

 public:
  std::vector<std::string> getImmediateChildrenOf(int stmt,
                                                  StmtType stmtType) override;

  std::vector<std::string> getImmediateParentOf(int stmt,
                                                StmtType stmtType) override;

  bool isParent(int stmt1, int stmt2) override;

  std::vector<std::pair<std::string, std::string>> getParentChildPairs(
      StmtType stmtType1, StmtType stmtType2) override;

  bool hasParents() override;

  // ================================ ParentT ================================

  std::vector<std::string> getChildrenStarOf(int stmt,
                                             StmtType stmtType) override;

  std::vector<std::string> getParentStarOf(int stmt,
                                           StmtType stmtType) override;

  bool isParentStar(int stmt1, int stmt2) override;

  std::vector<std::pair<std::string, std::string>> getParentChildStarPairs(
      StmtType stmtType1, StmtType stmtType2) override;

  bool hasParentsT() override;
};
