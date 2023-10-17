#pragma once

#include <string>
#include <utility>
#include <vector>

#include "qps/abstraction/AbstractionUtils.h"
#include "qps/abstraction/BaseAbstraction.h"
#include "qps/intermediateTable/IntermediateTable.h"

using GetAllStmtVarPairFuncType =
    vector<pair<string, string>> (PKBReader::*)(StmtType);
using GetAllProcVarPairFuncType =
    vector<pair<string, string>> (PKBReader::*)();
using GetStmtsRelatedToVarFuncType =
    vector<string> (PKBReader::*)(const string&, StmtType);
using GetProcsRelatedToVarFuncType =
    vector<string> (PKBReader::*)(const string&);
using GetVarsRelatedToStmtFuncType =
    vector<pair<string, string>> (PKBReader::*)(int, StmtType);
using GetVarsRelatedToProcFuncType =
    vector<string> (PKBReader::*)(const string&);
using IsVarRelatedToStmtFuncType = bool (PKBReader::*)(const string&,
                                                       const string&);
using IsVarRelatedToProcFunc = bool (PKBReader::*)(const string&,
                                                   const string&);

class StmtOrProcToVarAbstraction : public BaseAbstraction {
 private:
  GetAllStmtVarPairFuncType getAllStmtVarRelations;
  GetAllProcVarPairFuncType getAllProcVarRelations;
  GetStmtsRelatedToVarFuncType getStmtsRelatedToVar;
  GetProcsRelatedToVarFuncType getProcsRelatedToVar;
  GetVarsRelatedToStmtFuncType getVarsRelatedToStmt;
  GetVarsRelatedToProcFuncType getVarsRelatedToProc;
  IsVarRelatedToStmtFuncType isVarRelatedToStmt;
  IsVarRelatedToProcFunc isVarRelatedToProc;

  IntermediateTable handleSynonymOrWildcardArgs();
  IntermediateTable handleProcNameWithVarSynonymOrWildcard();

 protected:
  explicit StmtOrProcToVarAbstraction(
      AbstractionParams abstractionParams,
      GetAllStmtVarPairFuncType getAllStmtVarRelations,
      GetAllProcVarPairFuncType getAllProcVarRelations,
      GetStmtsRelatedToVarFuncType getStmtsRelatedToVar,
      GetProcsRelatedToVarFuncType getProcsRelatedToVar,
      GetVarsRelatedToStmtFuncType getVarsRelatedToStmt,
      GetVarsRelatedToProcFuncType getVarsRelatedToProc,
      IsVarRelatedToStmtFuncType isVarRelatedToStmt,
      IsVarRelatedToProcFunc isVarRelatedToProc)
      : BaseAbstraction(abstractionParams),
        getAllStmtVarRelations(getAllStmtVarRelations),
        getAllProcVarRelations(getAllProcVarRelations),
        getStmtsRelatedToVar(getStmtsRelatedToVar),
        getProcsRelatedToVar(getProcsRelatedToVar),
        getVarsRelatedToStmt(getVarsRelatedToStmt),
        getVarsRelatedToProc(getVarsRelatedToProc),
        isVarRelatedToStmt(isVarRelatedToStmt),
        isVarRelatedToProc(isVarRelatedToProc) {}

  IntermediateTable evaluateSynonymSynonym() override;
  IntermediateTable evaluateSynonymIdent() override;
  IntermediateTable evaluateSynonymWildcard() override;

  IntermediateTable evaluateIntegerSynonym() override;
  IntermediateTable evaluateIntegerIdent() override;
  IntermediateTable evaluateIntegerWildcard() override;

  IntermediateTable evaluateIdentSynonym() override;
  IntermediateTable evaluateIdentIdent() override;
  IntermediateTable evaluateIdentWildcard() override;
};
