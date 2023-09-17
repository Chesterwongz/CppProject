#pragma once

#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/PatternStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"

class PKBStorage {
public:
    PKBStorage();

    // FollowsStorage methods
    void setFollows(int statementNumber, int followingStatement);

    // ModifiesStorage methods
    void setVariableModification(const std::string& variableName, int statementNumber);

    // ParentStorage methods
    void setParent(int statementNumber, int childStatement);

    // UsesStorage methods
    void setVariableUsage(const std::string& variableName, int statementNumber);

    virtual void setVariable(const std::string& variableName);

    virtual void setConstant(const std::string& constantValue);

    virtual void setProcedure(const std::string& procedureName, int startStatement);

    virtual void setStatement(int statementNumber, StmtType statementType);

    virtual void setPattern(std::string variableName, std::string rpn, int statementNumber);

    std::set<std::string> getAllVariables();

    std::set<std::string> getAllConstants();

    std::set<std::string> getAllProcedures();

    std::set<int> getStatementNumbersFromStatementType(StmtType statementType);

    StmtType getStatementTypeFromStatementNumber(int statementNumber);

    int getImmediateFollows(int statementNumber);

    int getImmediateFollowedBy(int statementNumber);

    std::set<int> getAllFollows(int statementNumber);

    std::set<int> getAllFollowedBy(int statementNumber);

    std::set<int> getImmediateChildren(int statementNumber);

    int getImmediateParent(int statementNumber);

    std::set<int> getAllChildren(int statementNumber);

    std::set<int> getAllParents(int statementNumber);

    std::set<std::string> getModifiedVariablesForStatement(int statementNumber);

    std::set<std::string> getUsedVariablesForStatement(int statementNumber);

    std::set<int> getStatementNumbersForModifiedVariable(std::string variableName);

    std::set<int> getStatementNumbersForUsedVariable(std::string variableName);

    std::vector<std::string> getExactPattern(std::string variableName, std::string rpn);

    std::vector<std::string> getPartialPattern(std::string variableName, std::string rpn);

private:
    DesignEntitiesStorage designEntitiesStorage;
    FollowsStorage followsStorage;
    ModifiesStorage modifiesStorage;
    PatternStorage patternStorage;
    ParentStorage parentStorage;
    StatementStorage statementStorage;
    UsesStorage usesStorage;
};