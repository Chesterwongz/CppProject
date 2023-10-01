#pragma once
#include <string>
#include <vector>

#include "common/StmtTypes.h"


class IParentReader {
public:
    virtual std::vector<std::pair<std::string, std::string>> getImmediateChildrenOf(int statementNumber, StmtType statementType) = 0;
    virtual std::pair<std::string, std::string> getImmediateParentOf(int statementNumber, StmtType statementType) = 0;
    virtual bool isParent(int statementNumber, int childStatement) = 0;
    virtual std::vector<std::pair<std::string, std::string>> getParentChildPairs(StmtType parentType, StmtType childType) = 0;
    virtual std::vector<std::pair<std::string, std::string>> getChildrenStarOf(int statementNumber, StmtType statementType) = 0;
    virtual std::vector<std::pair<std::string, std::string>> getParentStarOf(int statementNumber, StmtType statementType) = 0;
    virtual bool isParentStar(int statementNumber, int childStatement) = 0;
    virtual std::vector<std::pair<std::string, std::string>> getParentChildStarPairs(StmtType parentType, StmtType childType) = 0;
};
