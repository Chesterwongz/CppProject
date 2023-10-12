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
#include "pkb/interfaces/writers/INextWriter.h"
#include "pkb/interfaces/writers/IParentWriter.h"
#include "pkb/interfaces/writers/IPatternWriter.h"
#include "pkb/interfaces/writers/IStatementWriter.h"
#include "pkb/interfaces/writers/IUsesWriter.h"

using std::unique_ptr, std::string, std::unordered_set, std::stack;

class PKBWriter : public IDesignEntitiesWriter,
                  public IFollowsWriter,
                  public IParentWriter,
                  public IModifiesWriter,
                  public IUsesWriter,
                  public ICallsWriter,
                  public IStatementWriter,
                  public IPatternWriter,
                  public INextWriter {
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
  void setModifiesRelationship(const std::string& variableName,
                               int statementNumber) override;

  // Add uses relationship
  void setUsesRelationship(const std::string& variableName,
                           int statementNumber) override;

  // Add variable name to storage
  void setVariable(const std::string& variableName) override;

  // Add constant value to storage
  void setConstant(const std::string& constantValue) override;

  // Add procedure name to storage
  void setProcForStmt(const std::string& procedureName,
                      int startStatement) override;

  // Add statement number and type to storage
  void setStatement(int statementNumber, StmtType statementType) override;

  virtual void setWhilePattern(int statementNumber, const std::string& varName);

  virtual void setIfPattern(int statementNumber, const std::string& varName);

  virtual void setUsesRelationship(const std::string& variableName,
                                   const std::string& procedureName);

  virtual void setModifiesRelationship(const std::string& variableName,
                                       const std::string& procedureName);

  // direct calls, not transitive
  void setCallsRelationship(const string& callerProc,
                            const string& calleeProc) override;

  void setCallsStarRelationship(const string& callerProc,
                                const string& calleeProc) override;

  // Add an expression to storage
  void setAssignPattern(const std::string& variableName, const std::string& rpn,
                        int statementNumber) override;

  void setIndirectCallsRelationship();

  virtual void setCFG(const std::string& procName, unique_ptr<CFG> cfg);

  void addNext(int from, int to) override;

 private:
  PKBStorage& storage;
  void setUsesForCalls(const string& callerProc,
                       const unordered_set<string>& calleeProc);
  void setModifiesForCalls(const string& callerProc,
                           const unordered_set<string>& calleeProc);
  void processCallRelations(
      const string& caller, const unordered_set<string>& callees,
      unordered_set<string> (PKBStorage::*retrieveVars)(const string&),
      void (PKBWriter::*setRelationship)(const string&, const string&));
};
