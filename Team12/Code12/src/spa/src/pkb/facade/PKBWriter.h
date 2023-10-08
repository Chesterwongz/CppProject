#pragma once

#include <memory>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/cfg/CFG.h"
#include "common/utils/PairUtils.h"
#include "pkb/facade/PKBStorage.h"
#include "pkb/interfaces/writers/ICallsWriter.h"
#include "pkb/interfaces/writers/IDesignEntitiesWriter.h"
#include "pkb/interfaces/writers/IFollowsWriter.h"
#include "pkb/interfaces/writers/IModifiesWriter.h"
#include "pkb/interfaces/writers/IParentWriter.h"
#include "pkb/interfaces/writers/IPatternWriter.h"
#include "pkb/interfaces/writers/IStatementWriter.h"
#include "pkb/interfaces/writers/IUsesWriter.h"

using std::unique_ptr, std::queue, std::string, std::unordered_set;

class PKBWriter : public virtual IDesignEntitiesWriter,
                  public virtual IFollowsWriter,
                  public virtual IParentWriter,
                  public virtual IModifiesWriter,
                  public virtual IUsesWriter,
                  public virtual ICallsWriter,
                  public virtual IStatementWriter,
                  public virtual IPatternWriter {
 public:
  explicit PKBWriter(PKBStorage& storage) : storage(storage) {}
  ~PKBWriter() override = default;

  // Add follows relationship
  void setFollowsRelationship(int statementNumber,
                              int followingStatement) override;

  // Add parent relationship
  void setParentRelationship(int statementNumber, int childStatement) override;

  // Add parent* relationship
  void setParentStarRelationship(int statementNumber,
                                 int childStatement) override;

  // Add modifies relationship
  void setModifiesRelationship(const string& variableName,
                               int statementNumber) override;
  virtual void setModifiesRelationship(const string& variableName,
                                       const string& procName);

  // Add uses relationship
  void setUsesRelationship(const string& variableName,
                           int statementNumber) override;
  virtual void setUsesRelationship(const string& variableName,
                                   const string& procName);

  // Add variable name to storage
  void setVariable(const string& variableName) override;

  // Add constant value to storage
  void setConstant(const string& constantValue) override;

  // Add procedure name to storage
  void setProcedure(const string& procedureName, int startStatement) override;

  // Add statement number and type to storage
  void setStatement(int statementNumber, StmtType statementType) override;

  virtual void setWhilePattern(int statementNumber, const string& varName);

  virtual void setIfPattern(int statementNumber, const string& varName);

  // direct calls, not transitive
  void setCallsRelationship(const string& callerProc, const string& calleeProc,
                            int stmtNum) override;

  void setCallsStarRelationship(const string& callerProc,
                                const string& calleeProc, int stmtNum) override;

  // Add an expression to storage
  void setAssignPattern(const string& variableName, const string& rpn,
                        int statementNumber) override;

  void setIndirectCallsRelationship();

  virtual void setCFG(const std::string& procName, unique_ptr<CFG> cfg);

 private:
  PKBStorage& storage;
  void setUsesForCalls(const string& callerProc, const string& calleeProc);
  void setModifiesForCalls(const string& callerProc, const string& calleeProc);
  void setRelationshipsForIndirectCalls(
      const string& caller,
      const unordered_set<pair<string, string>, PairUtils::PairHash>&
          visitedCallees);
};
