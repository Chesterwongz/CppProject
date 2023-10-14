#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/utils/VectorUtils.h"
#include "pkb/interfaces/readers/IParentReader.h"
#include "pkb/storage/ParentStore.h"
#include "pkb/storage/StmtStore.h"

class ParentReader : public IParentReader {
 private:
  ParentStore& parentStore;
  StmtStore& stmtStore;

 protected:
  explicit ParentReader(ParentStore& parent_storage,
                        StmtStore& statement_storage)
      : parentStore(parent_storage), stmtStore(statement_storage) {}

 public:
  std::vector<std::string> getImmediateChildrenOf(int stmt,
                                                  StmtType stmtType) override;

  std::vector<std::string> getImmediateParentOf(int stmt,
                                                StmtType stmtType) override;

  bool isParent(int stmt1, int stmt2) override;

  std::vector<std::pair<std::string, std::string>> getParentChildPairs(
      StmtType stmtType1, StmtType stmtType2) override;

  // ================================ ParentT ================================

  std::vector<std::string> getChildrenStarOf(int stmt,
                                             StmtType stmtType) override;

  std::vector<std::string> getParentStarOf(int stmt,
                                           StmtType stmtType) override;

  bool isParentStar(int stmt1, int stmt2) override;

  std::vector<std::pair<std::string, std::string>> getParentChildStarPairs(
      StmtType stmtType1, StmtType stmtType2) override;
};
