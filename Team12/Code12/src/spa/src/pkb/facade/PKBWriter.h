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

    // Add an expression to storage
    virtual void setAssignPattern(std::string variableName, std::string rpn, int statementNumber);

private:
    PKBStorage& storage;
};
