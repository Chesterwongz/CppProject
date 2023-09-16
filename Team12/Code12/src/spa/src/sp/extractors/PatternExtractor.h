#pragma once

#include <string>
#include "Extractor.h"
#include "sp/ast/statements/AssignNode.h"

class PatternExtractor : public Extractor {
private:
    std::string nodeToPostfixString(TNode *node);

public:
    explicit PatternExtractor(PKBWriter *pkbWriter);
    void visitAssign(const AssignNode *node) override;

};

