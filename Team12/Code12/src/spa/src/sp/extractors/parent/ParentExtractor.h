#pragma once

#include <stack>
#include <vector>

#include "sp/ast/StmtListNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/extractors/Extractor.h"

class ParentExtractor : public Extractor {
 private:
  std::stack<int> parents;

 public:
  explicit ParentExtractor(PKBWriter& pkbWriter);
  void visitIf(const IfNode& node) override;
  void visitWhile(const WhileNode& node) override;
  void visitStmtList(const StmtListNode& node) override;
  void postVisitIf(const IfNode& node) override;
  void postVisitWhile(const WhileNode& node) override;
};
