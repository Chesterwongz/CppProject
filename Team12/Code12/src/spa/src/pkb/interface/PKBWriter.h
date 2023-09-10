#pragma once

#include <string>
#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"

class PKBWriter {
public:
    // Constructor
    PKBWriter();

    // Add follows relationship
    void setFollowsRelationship(int statementNumber, int followingStatement);

    // Add parent relationship
    void setParentRelationship(int statementNumber, int childStatement);

    // Add modifies relationship
    void setModifiesRelationship(const std::string& variableName, int statementNumber);

    // Add uses relationship
    void setUsesRelationship(const std::string& variableName, int statementNumber);

    void setVariable(const std::string& variableName);

    void setConstant(int constantValue);

    void setProcedure(const std::string& procedureName, int startStatement);

    void setReadStatement(int statementNumber);

    void setPrintStatement(int statementNumber);

    void setAssignStatement(int statementNumber);

    void setCallStatement(int statementNumber);

    void setIfStatement(int statementNumber);

    void setWhileStatement(int statementNumber);

private:
    DesignEntitiesStorage designEntitiesStorage;
    FollowsStorage followsStorage;
    ModifiesStorage modifiesStorage;
    ParentStorage parentStorage;
    StatementStorage statementStorage;
    UsesStorage usesStorage;
};