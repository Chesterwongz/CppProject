#pragma once
#include <string>
#include <vector>
#include "common/StmtTypes.h"

class IUsesReader {
public:
    virtual std::vector<std::string> getStatementsUsing(const std::string& variableName, StmtType statementType) = 0;
    virtual std::vector<std::pair<std::string, std::string>> getVariablesUsedBy(int statementNumber, StmtType statementType) = 0;
    virtual bool isVariableUsedBy(const std::string& variableName, const std::string& statementNumber) = 0;
};
