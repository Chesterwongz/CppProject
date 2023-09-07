#include <vector>
#include <string>
#include <map>

class DesignEntitiesStorage {
public:
    DesignEntitiesStorage();

    void setVariable(const std::string& variableName, int statementNumber);

    void setConstant(int constantValue, int statementNumber);

    void setProcedure(const std::string& procedureName, int startStatement);

    std::vector<std::string> getAllVariables();

    std::vector<int> getAllConstants();

    std::vector<std::string> getAllProcedures();

    std::vector<std::string> getVariablesOnStatement(int statementNumber);

    std::vector<int> getStatementsOfVariable(const std::string& variableName);

    std::vector<int> getConstantsOnStatement(int statementNumber);

    std::vector<int> getStatementsOfConstant(int constantValue);

    std::vector<std::string> getProceduresOnStatement(int statementNumber);

    int getStartingStatementOfProcedure(const std::string& procedureName);

private:
    std::map<std::string, std::vector<int>> variableData;

    std::map<int, std::vector<int>> constantData;

    std::map<std::string, int> procedureData;
};
