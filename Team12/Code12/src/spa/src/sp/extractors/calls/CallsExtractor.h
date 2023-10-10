#pragma once

#include <string>

#include "sp/ast/ProcNode.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/statements/CallNode.h"
#include "sp/exceptions/CyclicProcCallException.h"
#include "sp/exceptions/UndefinedProcCallException.h"
#include "sp/extractors/Extractor.h"

class CallsExtractor : public Extractor {
 private:
  std::string currProc;

 public:
  explicit CallsExtractor(PKBWriter& pkbWriter);
  void visitProcedure(const ProcNode& node) override;
  void visitCall(const CallNode& node) override;
};
