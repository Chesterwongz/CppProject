#include "CallsExtractor.h"

CallsExtractor::CallsExtractor(PKBWriter& pkbWriter) : Extractor(pkbWriter) {}

void CallsExtractor::visitProcedure(const ProcNode& node) {
  currProc = node.getValue();
}

void CallsExtractor::visitCall(const CallNode& node) {
  std::string callee = node.getValue();
  pkbWriter.addCalls(currProc, callee, node.getLineNum());
}
