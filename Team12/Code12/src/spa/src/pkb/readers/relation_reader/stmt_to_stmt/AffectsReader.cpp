#include "AffectsReader.h"

std::vector<std::pair<std::string, std::string>> AffectsReader::getAffectsPairs() {
    std::vector<std::pair<std::string, std::string>> result;

    const auto assignStatements = stmtStore.getAllStmtsOf(StmtType::ASSIGN);

    for (const auto& assign : assignStatements) {
        std::unordered_set<std::string> done;
        std::string v = *modifiesSStore.getAllDirectSuccessorsOf(assign).begin();

        FindAffectsPairs(assign, assign, v, done, result);
    }

    /*for (const auto& pair : result) {
        std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
    }*/

    return result;
}

void AffectsReader::FindAffectsPairs(
    int originalStmt,
    int currentStmt,
    const std::string& variable,
    std::unordered_set<std::string>& done,
    std::vector<std::pair<std::string, std::string>>& result) {

    done.insert(std::to_string(currentStmt));

    for (auto& nextStmt : nextStore.getAllDirectSuccessorsOf(currentStmt)) {
        if (nextStmt == originalStmt &&
            usesSStore.hasDirectRelation(nextStmt, variable)) {
            result.emplace_back(std::to_string(originalStmt), std::to_string(nextStmt));
        }

        if (done.count(std::to_string(nextStmt)) > 0) {
            continue;
        }

        // if it is an ASSIGN statement, and it uses the variable
        if (stmtStore.getAllStmtsOf(StmtType::ASSIGN).count(nextStmt) > 0 &&
            usesSStore.hasDirectRelation(nextStmt, variable)) {
            result.emplace_back(std::to_string(originalStmt), std::to_string(nextStmt));
        }

        //// if it is an ASSIGN statement, and it modifies the variable then Affects cannot hold
        //if (stmtStore.getAllStmtsOf(StmtType::ASSIGN).count(nextStmt) > 0 &&
        //    modifiesSStore.hasDirectRelation(nextStmt, variable)) {
        //    continue;
        //}

        //// if it is a READ statement, and it modifies the variable then Affects cannot hold
        //if (stmtStore.getAllStmtsOf(StmtType::READ).count(nextStmt) > 0 &&
        //    modifiesSStore.hasDirectRelation(nextStmt, variable)) {
        //    continue;
        //}

        //// if it is a CALL statement, and it modifies the variable then Affects cannot hold
        //if (stmtStore.getAllStmtsOf(StmtType::CALL).count(nextStmt) > 0 &&
        //    modifies_storage_.getVarsModifiedByProc(calls_storage_.getStmtCalleeMap().at(nextStmt)).count(variable) > 0) {
        //    continue;
        //}

        if (modifiesSStore.hasDirectRelation(nextStmt, variable)) {
            continue;
        }

        FindAffectsPairs(originalStmt, nextStmt, variable, done, result);
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

