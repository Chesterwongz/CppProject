#pragma once

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/utils/CollectionUtils.h"
#include "pkb/interfaces/readers/IUsesReader.h"
#include "pkb/storage/entity_storage/StmtStore.h"
#include "pkb/storage/relation_storage/RelationStore.h"

class StmtOrProcToVarReader {
 private:
  RelationStore<int, std::string>& relationSStore;
  RelationStore<std::string, std::string>& relationPStore;
  StmtStore& stmtStore;

 public:
  explicit StmtOrProcToVarReader(
      RelationStore<int, std::string>& relationSStore,
      RelationStore<std::string, std::string>& relationPStore,
      StmtStore& stmtStore)
      : relationSStore(relationSStore),
        relationPStore(relationPStore),
        stmtStore(stmtStore) {}

  std::vector<std::string> getVarByStmt(int stmt);

  std::vector<std::string> getStmtByVar(const std::string& varName,
                                        StmtType stmtType);

  bool hasDirectRelation(int stmt, const std::string& varName);

  std::vector<std::pair<std::string, std::string>> getStmtVarPairs(
      StmtType stmtType1);

  std::vector<std::string> getVarByProc(const std::string& procName);

  std::vector<std::string> getProcByVar(const std::string& varName);

  bool hasDirectRelation(const std::string& procName,
                         const std::string& varName);

  std::vector<std::pair<std::string, std::string>> getProcVarPairs();
};
