#pragma once

#include <string>
#include <utility>
#include <vector>

#include "StmtToStmtReader.h"
#include "common/utils/CollectionUtils.h"
#include "pkb/interfaces/readers/INextReader.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/relation_storage/NextStore.h"

class NextReader : public INextReader {
 private:
  StmtToStmtReader reader;

 public:
  NextReader(NextStore& nextStore, StmtStore& stmtStore)
      : reader(nextStore, stmtStore) {}

  std::vector<std::pair<std::string, std::string>> getNextPairs(
      StmtType stmtType1, StmtType stmtType2) override;
  std::vector<std::pair<std::string, std::string>> getNextTPairs(
      StmtType stmtType1, StmtType stmtType2) override;

  bool isNext(int stmt1, int stmt2) override;
  bool isNextT(int stmt1, int stmt2) override;

  std::vector<std::string> getPrevStmts(int s2, StmtType stmtType1) override;
  std::vector<std::string> getPrevTStmts(int s2, StmtType stmtType1) override;

  std::vector<std::string> getNextStmts(int s1, StmtType stmtType2) override;
  std::vector<std::string> getNextTStmts(int s1, StmtType stmtType2) override;

  bool hasNext() override;
  bool hasNextT() override;
};
