#pragma once

#include <vector>
#include "Extractor.h"
#include "sp/ast/TNode.h"
#include "pkb/PkbWriter.h"

class DesignExtractor {
private:
    std::vector<std::unique_ptr<Extractor>> extractors;

public:
    explicit DesignExtractor(PkbWriter* pkbWriter);
    void extract(TNode* astRoot);
    void dfs(TNode* node);

};
