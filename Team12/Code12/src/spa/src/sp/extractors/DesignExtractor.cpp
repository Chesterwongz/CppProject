#include "DesignExtractor.h"

DesignExtractor::DesignExtractor() {
    extractors.emplace_back(std::make_unique<FollowsExtractor>());
    extractors.emplace_back(std::make_unique<ParentExtractor>());
    extractors.emplace_back(std::make_unique<UsesExtractor>());
    extractors.emplace_back(std::make_unique<ModifiesExtractor>());
    extractors.emplace_back(std::make_unique<EntityExtractor>());
}

DesignExtractor::DesignExtractor(PkbWriter* pkbWriter) {
    extractors.emplace_back(std::make_unique<FollowsExtractor>(pkbWriter));
//    extractors.emplace_back(std::make_unique<ParentExtractor>(pkbWriter));
//    extractors.emplace_back(std::make_unique<UsesExtractor>(pkbWriter));
//    extractors.emplace_back(std::make_unique<ModifiesExtractor>(pkbWriter));
}

void DesignExtractor::extract(TNode *node) {
    for (const auto &extractor : extractors) {
        node->accept(extractor.get());
    }
    for (auto child : node->getChildren()) {
        extract(child);
    }
    for (const auto &extractor : extractors) {
        node->cleanup(extractor.get());
    }
}

//void DesignExtractor::dfs(TNode *node) {
//    for (const auto &extractor : extractors) {
//        node->accept(extractor.get());
//    }
//    for (auto child : node->getChildren()) {
//        dfs(child);
//    }
//}

std::map<int, std::set<int>> DesignExtractor::getFollowsMap() {
    auto* followsExtractor = dynamic_cast<FollowsExtractor*>(extractors[0].get());
    return followsExtractor->getFollowsMap();
}

std::map<int, std::set<int>> DesignExtractor::getParentMap() {
    auto* parentExtractor = dynamic_cast<ParentExtractor*>(extractors[1].get());
    return parentExtractor->getParentMap();
}

std::map<std::string, std::set<int>> DesignExtractor::getUsesMap() {
    auto* usesExtractor = dynamic_cast<UsesExtractor*>(extractors[2].get());
    return usesExtractor->getUsesMap();
}

std::map<std::string, std::set<int>> DesignExtractor::getModifiesMap() {
    auto* modifiesExtractor = dynamic_cast<ModifiesExtractor*>(extractors[3].get());
    return modifiesExtractor->getModifiesMap();
}

std::unordered_set<std::string> DesignExtractor::getVariables() {
    auto* entityExtractor = dynamic_cast<EntityExtractor*>(extractors[4].get());
    return entityExtractor->getVariables();
}

std::unordered_set<std::string> DesignExtractor::getConstants() {
    auto* entityExtractor = dynamic_cast<EntityExtractor*>(extractors[4].get());
    return entityExtractor->getConstants();
}

std::unordered_set<std::string> DesignExtractor::getProcedures() {
    auto* entityExtractor = dynamic_cast<EntityExtractor*>(extractors[4].get());
    return entityExtractor->getProcedures();
}

std::unordered_set<int> DesignExtractor::getAssignStmts() {
    auto* entityExtractor = dynamic_cast<EntityExtractor*>(extractors[4].get());
    return entityExtractor->getAssignStmts();
}

std::unordered_set<int> DesignExtractor::getCallStmts() {
    auto* entityExtractor = dynamic_cast<EntityExtractor*>(extractors[4].get());
    return entityExtractor->getCallStmts();
}

std::unordered_set<int> DesignExtractor::getIfStmts() {
    auto* entityExtractor = dynamic_cast<EntityExtractor*>(extractors[4].get());
    return entityExtractor->getIfStmts();
}

std::unordered_set<int> DesignExtractor::getPrintStmts() {
    auto* entityExtractor = dynamic_cast<EntityExtractor*>(extractors[4].get());
    return entityExtractor->getPrintStmts();
}

std::unordered_set<int> DesignExtractor::getReadStmts() {
    auto* entityExtractor = dynamic_cast<EntityExtractor*>(extractors[4].get());
    return entityExtractor->getReadStmts();
}

std::unordered_set<int> DesignExtractor::getWhileStmts() {
    auto* entityExtractor = dynamic_cast<EntityExtractor*>(extractors[4].get());
    return entityExtractor->getWhileStmts();
}
