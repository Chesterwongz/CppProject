#pragma once

#include <vector>
#include <map>
#include <set>
#include "Extractor.h"
#include "sp/ast/TNode.h"
#include "pkb/PkbWriter.h"

class DesignExtractor {
private:
    std::vector<std::unique_ptr<Extractor>> extractors;

public:
    explicit DesignExtractor();  // TODO: remove this constructor after pkb integration
    explicit DesignExtractor(PkbWriter* pkbWriter);
    void extract(TNode* astRoot);
//    void dfs(TNode* node);
    std::map<int, std::set<int>> getFollowsMap();  // TODO: remove this method after pkb integration

};
