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
    // Constructor
    explicit PKBWriter(struct Storage& storage) : storage(storage) {};

    // Add follows relationship
    virtual void setFollowsRelationship(int statementNumber, int followingStatement);

    // Add parent relationship
    virtual void setParentRelationship(int statementNumber, int childStatement);

    // Add modifies relationship
    virtual void setModifiesRelationship(const std::string& variableName, int statementNumber);

    // Add uses relationship
    virtual void setUsesRelationship(const std::string& variableName, int statementNumber);

    virtual void setVariable(const std::string& variableName);

    virtual void setConstant(const std::string& constantValue);

    virtual void setProcedure(const std::string& procedureName, int startStatement);

    virtual void setStatement(int statementNumber, StmtType statementType);

    virtual void setPattern(std::string variableName, std::string rpn, int statementNumber);

private:
    struct Storage& storage;
};
