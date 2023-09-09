#pragma once

#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <string>
#include "Extractor.h"
#include "sp/ast/TNode.h"
#include "pkb/PkbWriter.h"
#include "FollowsExtractor.h"
#include "ParentExtractor.h"
#include "UsesExtractor.h"
#include "ModifiesExtractor.h"
#include "EntityExtractor.h"

class DesignExtractor {
private:
    std::vector<std::unique_ptr<Extractor>> extractors;

public:
    explicit DesignExtractor();  // TODO: remove this constructor after pkb integration
    explicit DesignExtractor(PkbWriter* pkbWriter);
    void extract(TNode* astRoot);
//    void dfs(TNode* node);
    std::map<int, std::set<int>> getFollowsMap();  // TODO: remove this method after pkb integration
    std::map<int, std::set<int>> getParentMap();  // TODO: remove this method after pkb integration
    std::map<std::string, std::set<int>> getUsesMap();  // TODO: remove this method after pkb integration
    std::map<std::string, std::set<int>> getModifiesMap();  // TODO: remove this method after pkb integration
    std::unordered_set<std::string> getVariables(); // TODO: remove this method after pkb integration
    std::unordered_set<std::string> getConstants(); // TODO: remove this method after pkb integration
    std::unordered_set<std::string> getProcedures(); // TODO: remove this method after pkb integration
    std::unordered_set<int> getAssignStmts();
    std::unordered_set<int> getCallStmts();
    std::unordered_set<int> getIfStmts();
    std::unordered_set<int> getPrintStmts();
    std::unordered_set<int> getReadStmts();
    std::unordered_set<int> getWhileStmts();
};
