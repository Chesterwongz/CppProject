#include "AffectsReader.h"

std::vector<std::pair<std::string, std::string>> AffectsReader::getAffectsPairs() {
    std::vector<std::pair<std::string, std::string>> result;

    const auto assignStatements = stmt_storage_.getStatementNumbersFromStatementType(StmtType::ASSIGN);

    for (const auto& assign : assignStatements) {
        unordered_set<std::string> done;
        std::string v = *modifies_storage_.getVarsModifiedByStmt(assign).begin();

        FindAffectsPairs(assign, assign, v, done, result);
    }

    /*for (const auto& pair : result) {
        std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
    }*/

    return result;
}

void AffectsReader::FindAffectsPairs(
    int originalStatement,
    int currentStatement,
    const std::string& variable,
    unordered_set<std::string>& done,
    std::vector<std::pair<std::string, std::string>>& result) {

    /*std::cout << "original: " << originalStatement << std::endl;
    std::cout << "current: " << currentStatement << std::endl;*/

    done.insert(std::to_string(currentStatement));

    for (auto& nextStatement : next_storage_.getNextStmts(currentStatement)) {
        if (done.count(std::to_string(nextStatement)) > 0) {
            continue;
        }

        if (stmt_storage_.getStatementNumbersFromStatementType(StmtType::ASSIGN).count(nextStatement) > 0 &&
            uses_storage_.getVarsUsedByStmt(nextStatement).count(variable) > 0) {
            result.emplace_back(std::to_string(originalStatement), std::to_string(nextStatement));
        }

        if (modifies_storage_.getVarsModifiedByStmt(nextStatement).count(variable) > 0) {
            continue;
        }

        if (stmt_storage_.getStatementNumbersFromStatementType(StmtType::READ).count(nextStatement) > 0 &&
            modifies_storage_.getVarsModifiedByStmt(nextStatement).count(variable) > 0) {
            continue;
        }

        if (stmt_storage_.getStatementNumbersFromStatementType(StmtType::CALL).count(nextStatement) > 0 &&
            modifies_storage_.getVarsModifiedByProc(calls_storage_.getStmtCalleeMap().at(nextStatement)).count(variable) > 0) {
            continue;
        }

        FindAffectsPairs(originalStatement, nextStatement, variable, done, result);
    }
}

bool AffectsReader::isAffects(int firstStmtNum, int secondStmtNum) {
    std::vector<std::pair<std::string, std::string>> affectsPairs = getAffectsPairs();
    std::string firstStmtStr = std::to_string(firstStmtNum);
    std::string secondStmtStr = std::to_string(secondStmtNum);

    for (const auto& pair : affectsPairs) {
        if (pair.first == firstStmtStr && pair.second == secondStmtStr) {
            return true;
        }
    }

    return false;
}

std::vector<std::string> AffectsReader::getAffects(int firstStmtNum) {
    std::vector<std::string> result;

    const auto affectsPairs = getAffectsPairs();
    std::string firstStmtStr = std::to_string(firstStmtNum);

    for (const auto& pair : affectsPairs) {
        if (pair.first == firstStmtStr) {
            result.push_back(pair.second);
        }
    }

    return result;
}

std::vector<std::string> AffectsReader::getAffectedBy(int secondStmtNum) {
    std::vector<std::string> result;

    const auto affectsPairs = getAffectsPairs();
    std::string secondStmtStr = std::to_string(secondStmtNum);

    for (const auto& pair : affectsPairs) {
        if (pair.second == secondStmtStr) {
            result.push_back(pair.first);
        }
    }

    return result;
}

