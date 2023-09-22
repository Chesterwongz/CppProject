#pragma once

#include <string>
#include <memory>

#include "pkb/facade/PKBStorage.h"
#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"

using std::unique_ptr;

class PKBWriter {
public:
    explicit PKBWriter(PKBStorage& storage) : storage(storage) {};
    virtual ~PKBWriter() = default;

    // Add follows relationship
    virtual void setFollowsRelationship(int statementNumber, int followingStatement);

    // Add parent relationship
    virtual void setParentRelationship(int statementNumber, int childStatement);

    // Add parent* relationship
    virtual void setParentStarRelationship(int statementNumber, int childStatement);

    // Add modifies relationship
    virtual void setModifiesRelationship(const std::string& variableName, int statementNumber);

    // Add uses relationship
    virtual void setUsesRelationship(const std::string& variableName, int statementNumber);

    // Add variable name to storage
    virtual void setVariable(const std::string& variableName);

    // Add constant value to storage
    virtual void setConstant(const std::string& constantValue);

    // Add procedure name to storage
    virtual void setProcedure(const std::string& procedureName, int startStatement);

    // Add statement number and type to storage
    virtual void setStatement(int statementNumber, StmtType statementType);

    virtual void setWhilePattern(int statementNumber, const std::string& varName);

    virtual void setIfPattern(int statementNumber, const std::string& varName);

    virtual void setUsesRelationship(const std::string& variableName, const std::string& procedureName);

    virtual void setModifiesRelationship(const std::string& variableName, const std::string& procedureName);

    // direct calls, not transitive
    virtual void setCallsRelationship(const std::string& callerProc, const std::string& calleeProc);

    virtual void setCallsStarRelationship(const std::string& callerProc, const std::string& calleeProc);

    // Add an expression to storage
    virtual void setAssignPattern(std::string& variableName, std::string& rpn, int statementNumber);

private:
    PKBStorage& storage;
};
