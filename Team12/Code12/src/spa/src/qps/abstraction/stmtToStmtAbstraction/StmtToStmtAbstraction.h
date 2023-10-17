#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/abstraction/BaseAbstraction.h"
#include "qps/intermediateTable/IntermediateTable.h"

using GetAllStmtStmtPairsFuncType = vector<pair<string, string>> (PKBReader::*)(
    StmtType firstStmtType, StmtType secondStmtType);
using IsRelationTrueFuncType = bool (PKBReader::*)(int firstStmtNum,
                                                   int secondStmtNum);

class StmtToStmtAbstraction : public BaseAbstraction {
 private:
  GetAllStmtStmtPairsFuncType getAllStmtStmtPairs;
  IsRelationTrueFuncType isRelationTrue;

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
   * For handling cases where both args are non-integer
   */
  virtual IntermediateTable handleSynonymOrWildcardArgs() = 0;

  /**
   * For handling cases where both args are stmtNumbers
   */
  virtual IntermediateTable handleBothArgsInteger() = 0;

  /**
   * For handling cases where only first arg is stmtNumber
   */
  virtual IntermediateTable handleFirstArgInteger() = 0;

  /**
   * For handling cases where only second arg is stmtNumber
   */
  virtual IntermediateTable handleSecondArgInteger() = 0;

  explicit StmtToStmtAbstraction(
      AbstractionParams &abstractionParams,
      GetAllStmtStmtPairsFuncType getAllStmtStmtPairs,
      IsRelationTrueFuncType isRelationTrue)
      : BaseAbstraction(abstractionParams),
        getAllStmtStmtPairs(getAllStmtStmtPairs),
        isRelationTrue(isRelationTrue) {}
};
