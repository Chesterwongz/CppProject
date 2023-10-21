#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/abstraction/BaseAbstraction.h"
#include "qps/abstraction/SynResConversionUtils.h"
#include "qps/intermediateTable/IntermediateTable.h"

class StmtToStmtAbstraction : public BaseAbstraction {
 private:
  void filterSelfRefPairs(vector<pair<string, string>>& stmtPairs);
  virtual bool isSelfReferencePossible();
  virtual bool isFirstStmtTypeInvalid();
  virtual bool isSecondStmtTypeInvalid();

  /**
   * For handling cases where both args are non-integer and there is at most
   * one wildcard
   */
  IntermediateTable handleSynonymOrWildcardArgs();

  /**
   * For handling cases where both args wildcards
   */
  IntermediateTable handleBothArgsWildcard();

  /**
   * For handling cases where both args are stmtNumbers
   */
  IntermediateTable handleBothArgsInteger();

  /**
   * For handling cases where only first arg is stmtNumber
   */
  IntermediateTable handleFirstArgInteger();

  /**
   * For handling cases where only second arg is stmtNumber
   */
  IntermediateTable handleSecondArgInteger();

  IntermediateTable evaluateSynonymSynonym() override;
  IntermediateTable evaluateSynonymInteger() override;
  IntermediateTable evaluateSynonymWildcard() override;

  IntermediateTable evaluateIntegerSynonym() override;
  IntermediateTable evaluateIntegerInteger() override;
  IntermediateTable evaluateIntegerWildcard() override;

  IntermediateTable evaluateWildcardSynonym() override;
  IntermediateTable evaluateWildcardInteger() override;
  IntermediateTable evaluateWildcardWildcard() override;

 protected:
  /**
   * Abstraction(a, b): get all a, b pairs where a and b has specified stmtType
   */
  virtual vector<pair<string, string>> getAllPairs(StmtType firstStmtType,
                                                   StmtType secondStmtType) = 0;

  /**
   * Abstraction(a, b): get all stmt a where a has specified stmtType
   * and b has specified stmtNumber
   */
  virtual vector<string> getFirstStmt(int secondStmtNumber,
                                      StmtType firstStmtType) = 0;

  /**
   * Abstraction(a, b): get all stmt b where b has specified stmtType
   * and a has specified stmtNumber
   */
  virtual vector<string> getSecondStmt(int firstStmtNumber,
                                       StmtType secondStmtType) = 0;

  /**
   * Abstraction(a, b): check if specified stmtNum and stmtNum are related
   */
  virtual bool isStmtRelatedToStmt(int stmtNum1, int stmtNum2) = 0;

  explicit StmtToStmtAbstraction(AbstractionParams& abstractionParams)
      : BaseAbstraction(abstractionParams) {}
};
