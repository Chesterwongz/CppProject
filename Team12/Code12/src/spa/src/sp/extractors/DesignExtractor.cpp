#include "DesignExtractor.h"
#include "FollowsExtractor.h"
#include "ParentExtractor.h"
#include "UsesExtractor.h"
#include "ModifiesExtractor.h"

DesignExtractor::DesignExtractor(PkbWriter* pkbWriter) {
    extractors.emplace_back(std::make_unique<FollowsExtractor>(pkbWriter));
    extractors.emplace_back(std::make_unique<ParentExtractor>(pkbWriter));
    extractors.emplace_back(std::make_unique<UsesExtractor>(pkbWriter));
    extractors.emplace_back(std::make_unique<ModifiesExtractor>(pkbWriter));
}

void DesignExtractor::extract(TNode *node) {
    for (const auto &extractor : extractors) {
        node->accept(extractor.get());
    }
    for (auto child : node->getChildren()) {
        extract(child);
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

