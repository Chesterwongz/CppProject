#pragma once

#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#include "sp/ast/ProcNode.h"
#include "sp/ast/statements/AssignNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/ReadNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/ast/terminals/VarNode.h"
#include "sp/extractors/Extractor.h"

struct ModifiesStmtState {
  int lineNum;
  std::unordered_set<std::string> varsModified;
  bool isAnticipateVar = false;
};

class ModifiesExtractor : public Extractor {
 private:
  std::vector<ModifiesStmtState> stmtStates;
  std::string procName;
  void processCurrState();
  void postVisit();
  void addModifies(int lineNum, const std::string& var);

 public:
  explicit ModifiesExtractor(PKBWriter& pkbWriter);
  void visitProcedure(const ProcNode& node) override;
  void visitAssign(const AssignNode& node) override;
  void visitIf(const IfNode& node) override;
  void visitWhile(const WhileNode& node) override;
  void visitRead(const ReadNode& node) override;
  void visitVariable(const VarNode& node) override;
  void postVisitAssign(const AssignNode& node) override;
  void postVisitIf(const IfNode& node) override;
  void postVisitWhile(const WhileNode& node) override;
  void postVisitRead(const ReadNode& node) override;
};
