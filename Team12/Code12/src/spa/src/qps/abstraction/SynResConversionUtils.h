#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/intermediateTable/synonymRes/SynonymRes.h"
#include "qps/intermediateTable/synonymRes/SynonymResFactory.h"

using std::pair;

typedef std::function<SynonymRes(const string&, PKBReader&)> ToSynonymResFunc;

namespace SynResConversionUtils {
inline ToSynonymResFunc constantToSynonymRes = [](const string& constant,
                                                  PKBReader& pkbReader) {
  return SynonymResFactory::buildConstantSynonym(constant);
};

inline ToSynonymResFunc callToSynonymRes = [](const string& stmtNum,
                                              PKBReader& pkbReader) {
  string procName =
      pkbReader.getProcCalledBy(stoi(stmtNum)).at(CollectionUtils::FIRST_ELEM);
  return SynonymResFactory::buildCallsSynonym(stmtNum, procName);
};

inline ToSynonymResFunc printToSynonymRes = [](const string& stmtNum,
                                               PKBReader& pkbReader) {
  string varName = pkbReader.getVariablePrintedBy(stoi(stmtNum))
                       .at(CollectionUtils::FIRST_ELEM);
  return SynonymResFactory::buildPrintSynonym(stmtNum, varName);
};

inline ToSynonymResFunc procToSynonymRes = [](const string& procName,
                                              PKBReader& pkbReader) {
  return SynonymResFactory::buildProcSynonym(procName);
};

inline ToSynonymResFunc readToSynonymRes = [](const string& stmtNum,
                                              PKBReader& pkbReader) {
  string varName = pkbReader.getVariableReadBy(stoi(stmtNum)).at(0);
  return SynonymResFactory::buildReadSynonym(stmtNum, varName);
};

inline ToSynonymResFunc stmtToSynonymRes = [](const string& stmtNum,
                                              PKBReader& pkbReader) {
  return SynonymResFactory::buildStmtSynonym(stmtNum);
};

inline ToSynonymResFunc varToSynonymRes = [](const string& varName,
                                             PKBReader& pkbReader) {
  return SynonymResFactory::buildVarSynonym(varName);
};

inline ToSynonymResFunc defaultToSynonymRes = [](const string& datum,
                                                 PKBReader& pkbReader) {
  return SynonymResFactory::buildDefaultSynonym(datum);
};

inline const unordered_map<Entity, ToSynonymResFunc> EntityToFuncMap = {
    {ASSIGN_ENTITY, SynResConversionUtils::stmtToSynonymRes},
    {CALL_ENTITY, SynResConversionUtils::callToSynonymRes},
    {CONSTANT_ENTITY, SynResConversionUtils::constantToSynonymRes},
    {IF_ENTITY, SynResConversionUtils::stmtToSynonymRes},
    {PRINT_ENTITY, SynResConversionUtils::printToSynonymRes},
    {PROCEDURE_ENTITY, SynResConversionUtils::procToSynonymRes},
    {READ_ENTITY, SynResConversionUtils::readToSynonymRes},
    {STMT_ENTITY, SynResConversionUtils::stmtToSynonymRes},
    {VARIABLE_ENTITY, SynResConversionUtils::varToSynonymRes},
    {WHILE_ENTITY, SynResConversionUtils::stmtToSynonymRes},
    {INVALID_ENTITY, SynResConversionUtils::defaultToSynonymRes}};

vector<SynonymRes> toSynonymRes(const vector<string>& res,
                                const Entity& argEntity, PKBReader& pkbReader);

vector<vector<SynonymRes>> toSynonymRes(const vector<pair<string, string>>& res,
                                        const pair<Entity, Entity>& argPair,
                                        PKBReader& pkbReader);
}  // namespace SynResConversionUtils
