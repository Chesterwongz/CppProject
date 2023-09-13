#pragma once

#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <string>
#include "Extractor.h"
#include "sp/ast/TNode.h"
#include "FollowsExtractor.h"
#include "ParentExtractor.h"
#include "UsesExtractor.h"
#include "ModifiesExtractor.h"
#include "EntityExtractor.h"
#include "pkb/facade/PKBWriter.h"
#include "Populator.h"

class DesignExtractor {
private:
    std::vector<std::unique_ptr<Extractor>> extractors;
    Populator populator;

public:
    explicit DesignExtractor(PKBWriter* pkbWriter);
    void extract(TNode* node);
};
