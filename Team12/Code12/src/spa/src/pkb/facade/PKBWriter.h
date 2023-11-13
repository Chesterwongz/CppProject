#pragma once

#include <memory>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/utils/PairUtils.h"
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
  explicit PKBWriter(PKBStore& store)
      : usesPStore(store.getUsesProcStore()),
        modifiesPStore(store.getModifiesProcStore()),
        parentStore(store.getParentStore()),
        callsPStore(store.getCallsStore()),
        callsSStore(store.getCallsStmtStore()),
        followsStore(store.getFollowsStore()),
        DesignEntitiesWriter(store.getEntityStore(), store.getStmtStore()),
        FollowsWriter(store.getFollowsStore()),
        ModifiesWriter(store.getModifiesStore(), store.getModifiesProcStore()),
        NextWriter(store.getNextStore()),
        ParentWriter(store.getParentStore()),
        PatternWriter(store.getPatternStore()),
        UsesWriter(store.getUsesStore(), store.getUsesProcStore()),
        CallsWriter(store.getCallsStore(), store.getCallsStmtStore()) {}

  void computeAllRelationsT();

 private:
  RelationStore<std::string, std::string>& usesPStore;
  RelationStore<std::string, std::string>& modifiesPStore;
  RelationTStore<int>& parentStore;
  RelationTStore<int>& followsStore;
  RelationTStore<std::string>& callsPStore;
  RelationStore<int, std::string>& callsSStore;

  void addUsesForCallsProc(const string& callerProc,
                           const unordered_set<string>& calleeProcs);
  void addModifiesForCallProcs(const string& callerProc,
                               const unordered_set<string>& calleeProcs);
  template <typename ProcStoreType>
  void addRelationsForCallProcs(
      const string& callerProc, const unordered_set<string>& calleeProcs,
      const ProcStoreType& procStore,
      std::function<void(const string&, const string&)>& adder);

  template <typename ProcStoreType>
  void addRelationsForCallStmts(int stmtNum,
                                const unordered_set<string>& allCallees,
                                const ProcStoreType& procStore,
                                std::function<void(const string&, int)>& adder);

  void addUsesForCallStmts(int stmtNum,
                           const unordered_set<string>& allCallees);
  void addModifiesForCallStmts(int stmtNum,
                               const unordered_set<string>& allCallees);
  void setIndirectCallsRelationship();
  void setIndirectCallsProcRelationships();
  void setIndirectCallsStmtRelationships();
};
