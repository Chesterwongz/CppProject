#pragma once

#include <memory>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/cfg/CFG.h"
#include "common/utils/PairUtils.h"
#include "pkb/facade/PKBStorage.h"
#include "pkb/facade/PKBStore.h"
#include "pkb/writers/entity_writer/DesignEntitiesWriter.h"
#include "pkb/writers/pattern_writer/PatternWriter.h"
#include "pkb/writers/relation_writer/proc_to_proc/CallsWriter.h"
#include "pkb/writers/relation_writer/stmt_proc_to_var/ModifiesWriter.h"
#include "pkb/writers/relation_writer/stmt_proc_to_var/UsesWriter.h"
#include "pkb/writers/relation_writer/stmt_to_stmt/FollowsWriter.h"
#include "pkb/writers/relation_writer/stmt_to_stmt/NextWriter.h"
#include "pkb/writers/relation_writer/stmt_to_stmt/ParentWriter.h"

using std::unique_ptr, std::string, std::unordered_set, std::stack;

class PKBWriter : public DesignEntitiesWriter,
                  public FollowsWriter,
                  public ModifiesWriter,
                  public NextWriter,
                  public PatternWriter,
                  public ParentWriter,
                  public UsesWriter,
                  public CallsWriter {
 public:
  PKBWriter(PKBStorage& storage, PKBStore& store)
      : storage(storage),
        store(store),
        DesignEntitiesWriter(storage, store.getStmtStore()),
        FollowsWriter(store.getFollowsStore()),
        ModifiesWriter(store.getModifiesStore(), store.getModifiesProcStore()),
        NextWriter(store.getNextStore()),
        ParentWriter(store.getParentStore()),
        PatternWriter(storage),
        UsesWriter(store.getUsesStore(), store.getUsesProcStore()),
        CallsWriter(store.getCallsStore()) {}

  void setIndirectCallsRelationship();

  virtual void setCFG(const std::string& procName, unique_ptr<CFG> cfg);

 private:
  PKBStorage& storage;
  PKBStore& store;
  void setUsesForCalls(const string& callerProc,
                       const unordered_set<string>& calleeProc);
  void setModifiesForCalls(const string& callerProc,
                           const unordered_set<string>& calleeProc);
  void processCallProcRelations(
      const string& caller, const unordered_set<string>& callees,
      unordered_set<string> (PKBStorage::*retrieveVars)(const string&),
      void (PKBWriter::*setProcRelationship)(const string&, const string&));
  void processCallStmtRelations(
      int stmtNum, const string& callee,
      const unordered_set<string>& indirectCallees,
      unordered_set<string> (PKBStorage::*retrieveVars)(const string&),
      void (PKBWriter::*setStmtRelationship)(const string&, int));
};
