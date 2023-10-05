#pragma once

#include <map>
#include <set>
#include <vector>

#include "sp/ast/StmtListNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/extractors/Extractor.h"

class ParentExtractor : public Extractor {
 private:
  std::vector<int> parents;
  void addParent(int parent, int child);
  void addParentStar(int parent, int child);

 public:
  explicit ParentExtractor(PKBWriter& pkbWriter);
  void visitIf(const IfNode& node) override;
  void visitWhile(const WhileNode& node) override;
  void visitStmtList(const StmtListNode& node) override;
  void postVisitIf(const IfNode& node) override;
  void postVisitWhile(const WhileNode& node) override;
};
