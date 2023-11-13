#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/abstraction/AbstractionUtils.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/intermediateTable/IntermediateTable.h"

class ProcToProcAbstraction : public BaseAbstraction {
 private:
  bool isFirstSynonymInvalid() override;
  bool isSecondSynonymInvalid() override;

  IntermediateTable handleSynonymOrWildcardArgs();
  IntermediateTable handleFirstArgIdent(const string& firstArgValue);
  IntermediateTable handleSecondArgIdent(const string& secondArgValue);
  IntermediateTable handleBothArgsIdent();

  /**
   * Abstraction(a, b): a, b pairs exists
   */
  virtual bool hasPairs() = 0;

  /**
   * Abstraction(a, b): get all a, b pairs satisfying abstraction
   */
  virtual vector<pair<string, string>> getAllAbstractionPairs() = 0;

  /**
   * Abstraction(a, b): get all proc a where b has specified procName
   */
  virtual vector<string> getFirstProcInAbstraction(
      const string& secondProcName) = 0;

  /**
   * Abstraction(a, b): get all proc b where a has specified procName
   */
  virtual vector<string> getSecondProcInAbstraction(
      const string& firstProcName) = 0;

  /**
   * Abstraction(a, b): check if procName a and b are related
   */
  virtual bool isProcRelatedToProc(const string& firstProcName,
                                   const string& secondProcName) = 0;

 protected:
  explicit ProcToProcAbstraction(AbstractionParams abstractionParams)
      : BaseAbstraction(abstractionParams) {}

  IntermediateTable evaluateSynonymSynonym() override;
  IntermediateTable evaluateSynonymIdent() override;
  IntermediateTable evaluateSynonymWildcard() override;

  IntermediateTable evaluateIdentSynonym() override;
  IntermediateTable evaluateIdentIdent() override;
  IntermediateTable evaluateIdentWildcard() override;

  IntermediateTable evaluateWildcardSynonym() override;
  IntermediateTable evaluateWildcardIdent() override;
  IntermediateTable evaluateWildcardWildcard() override;
};
