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
#include "pkb/interfaces/writers/ICallsWriter.h"
#include "pkb/interfaces/writers/IDesignEntitiesWriter.h"
#include "pkb/interfaces/writers/IFollowsWriter.h"
#include "pkb/interfaces/writers/IModifiesWriter.h"
#include "pkb/interfaces/writers/IParentWriter.h"
#include "pkb/interfaces/writers/IPatternWriter.h"
#include "pkb/interfaces/writers/IStatementWriter.h"
#include "pkb/interfaces/writers/IUsesWriter.h"

using std::unique_ptr, std::string, std::unordered_set, std::stack;
using StmtProcPairsSet =
    unordered_set<pair<string, string>, PairUtils::PairHash>;

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
  virtual ~PKBWriter() = default;

  // Add follows relationship
  virtual void setFollowsRelationship(int statementNumber,
                                      int followingStatement);

  // Add parent relationship
  virtual void setParentRelationship(int statementNumber, int childStatement);

  // Add parent* relationship
  virtual void setParentStarRelationship(int statementNumber,
                                         int childStatement);

  // Add modifies relationship
  virtual void setModifiesRelationship(const std::string& variableName,
                                       int statementNumber);

  // Add uses relationship
  virtual void setUsesRelationship(const std::string& variableName,
                                   int statementNumber);

  // Add variable name to storage
  virtual void setVariable(const std::string& variableName);

  // Add constant value to storage
  virtual void setConstant(const std::string& constantValue);

  // Add procedure name to storage
  virtual void setProcedure(const std::string& procedureName,
                            int startStatement);

  // Add statement number and type to storage
  virtual void setStatement(int statementNumber, StmtType statementType);

  virtual void setWhilePattern(int statementNumber, const std::string& varName);

  virtual void setIfPattern(int statementNumber, const std::string& varName);

  virtual void setUsesRelationship(const std::string& variableName,
                                   const std::string& procedureName);

  virtual void setModifiesRelationship(const std::string& variableName,
                                       const std::string& procedureName);

  // direct calls, not transitive
  void setCallsRelationship(const string& callerProc, const string& calleeProc,
                            int stmtNum) override;

  void setCallsStarRelationship(const string& callerProc,
                                const string& calleeProc, int stmtNum) override;

  // Add an expression to storage
  virtual void setAssignPattern(const std::string& variableName,
                                const std::string& rpn, int statementNumber);

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
  void insertDirectCalleesOfProc(stack<pair<string, string>>& toVisit,
                                 const StmtProcPairsSet& visitedCallees,
                                 const string& currProc);
};
