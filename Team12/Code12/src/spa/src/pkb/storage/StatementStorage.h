#ifndef STATEMENT_STORAGE_H
#define STATEMENT_STORAGE_H

#include <vector>
#include <map>
#include <string>

class StatementStorage {
public:
    // Constructor
    StatementStorage();

    // Setter
    void setStatement(const std::string& statementType, int statementNumber);

    // First Getter
    std::vector<int> getStatementNumbersFromStatementType(const std::string& statementType);

    // Second Getter
    std::vector<std::string> getStatementTypesFromStatementNumber(int statementNumber);

private:
    // Data structure for statement storage (statement type -> line numbers)
    std::map<std::string, std::vector<int>> statementStorage;
};

#endif // STATEMENT_STORAGE_H
