#include "DesignExtractor.h"
#include "FollowsExtractor.h"
#include "ParentExtractor.h"
#include "UsesExtractor.h"
#include "ModifiesExtractor.h"

DesignExtractor::DesignExtractor() {
    extractors.emplace_back(std::make_unique<FollowsExtractor>());
    extractors.emplace_back(std::make_unique<ParentExtractor>());
    extractors.emplace_back(std::make_unique<UsesExtractor>());
    extractors.emplace_back(std::make_unique<ModifiesExtractor>());
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