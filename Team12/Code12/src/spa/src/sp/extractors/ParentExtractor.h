#pragma once

#include <vector>
#include <map>
#include <set>
#include "Extractor.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/ast/StmtListNode.h"

class ParentExtractor : public Extractor {
private:
    std::vector<int> parents;
    std::map<int, std::set<int>> parentsMap; // child, parents

public:
    explicit ParentExtractor();
    explicit ParentExtractor(PkbWriter *pkbWriter);
    void visitIf(const IfNode *node) override;
    void visitWhile(const WhileNode *node) override;
    void visitStmtList(const StmtListNode *node) override;
    void postVisitIf(const IfNode *node) override;
    void postVisitWhile(const WhileNode *node) override;
    std::map<int, std::set<int>> getParentMap();

};
