#pragma once

#include <string>
#include <utility>
#include <vector>

#include "pkb/facade/PKB.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/procToProcAbstraction/ProcToProcAbstraction.h"
#include "qps/abstraction/stmtOrProcToVarAbstraction/StmtOrProcToVarAbstraction.h"

class CallsStarAbstraction : public ProcToProcAbstraction {
 private:
  bool hasPairs() override;

  vector<pair<string, string>> getAllAbstractionPairs() override;

  vector<string> getFirstProcInAbstraction(
      const string& secondProcName) override;

  vector<string> getSecondProcInAbstraction(
      const string& firstProcName) override;

  bool isProcRelatedToProc(const string& firstProcName,
                           const string& secondProcName) override;

 public:
  explicit CallsStarAbstraction(AbstractionParams abstractionParams)
      : ProcToProcAbstraction(abstractionParams) {}
};
