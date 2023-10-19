#pragma once

#include <map>
#include <set>
#include <stack>
#include <vector>

#include "pkb/facade/PKBWriter.h"
#include "sp/ast/StmtListNode.h"
#include "sp/ast/statements/AssignNode.h"
#include "sp/ast/statements/CallNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/PrintNode.h"
#include "sp/ast/statements/ReadNode.h"
#include "sp/ast/statements/StmtNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/extractors/Extractor.h"

class FollowsExtractor : public Extractor {
 private:
  // each element is the previous line in
  // a nesting block, e.g. proc, if, while {}
  std::stack<int> nestingBlocksStack;
  void processCurrStmt(const StmtNode& node);

 public:
  explicit FollowsExtractor(PKBWriter& pkbWriter);
  void visitAssign(const AssignNode& node) override;
  void visitCall(const CallNode& node) override;
  void visitIf(const IfNode& node) override;
  void visitPrint(const PrintNode& node) override;
  void visitRead(const ReadNode& node) override;
  void visitWhile(const WhileNode& node) override;
  void visitStmtList(const StmtListNode& node) override;
  void postVisitStmtList(const StmtListNode& node) override;
};
