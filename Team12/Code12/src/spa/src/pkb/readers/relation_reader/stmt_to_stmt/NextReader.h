#pragma once

#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/Constants.h"
#include "common/utils/CollectionUtils.h"
#include "pkb/interfaces/readers/INextReader.h"
#include "pkb/storage/NextStore.h"
#include "pkb/storage/StmtStore.h"

class NextReader : public INextReader {
 private:
  NextStore& nextStore;
  StmtStore& stmtStore;

 public:
  NextReader(NextStore& nextStore, StmtStore& stmtStore)
      : nextStore(nextStore), stmtStore(stmtStore) {}

  std::vector<std::pair<std::string, std::string>> getNextPairs(
      StmtType stmtType1, StmtType stmtType2) override;
  std::vector<std::pair<std::string, std::string>> getNextTPairs(
      StmtType stmtType1, StmtType stmtType2) override;

  bool isNext(int stmt1, int stmt2) override;
  bool isNextT(int stmt1, int stmt2) override;

  std::vector<std::string> getPrevStmts(int stmt2, StmtType stmtType1) override;
  std::vector<std::string> getPrevTStmts(int stmt2,
                                         StmtType stmtType1) override;

  std::vector<std::string> getNextStmts(int stmt1, StmtType stmtType2) override;
  std::vector<std::string> getNextTStmts(int stmt1,
                                         StmtType stmtType2) override;
};
