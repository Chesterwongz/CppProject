//#pragma once
//
//#include <functional>
//#include <memory>
//#include <string>
//#include <unordered_map>
//#include <utility>
//
//#include "pkb/facade/PKBReader.h"
//#include "qps/argument/AbstractArgument.h"
//#include "qps/argument/synonymArg/SynonymArg.h"
//#include "qps/clause/withClause/WithClauseUtils.h"
//#include "qps/common/Keywords.h"
//#include "qps/intermediateTable/IntermediateTable.h"
//#include "qps/withEvaluator/WithEvaluator.h"
//
//using std::unique_ptr, std::string, std::move, std::pair, std::make_pair,
//    std::function, std::make_unique;
//
//class DoubleSynWithEvaluator : public WithEvaluator {
// protected:
//  unique_ptr<SynonymArg> firstSynonymArg;
//  unique_ptr<SynonymArg> secondSynonymArg;
//
//  IntermediateTable evaluateStmtNum(PKBReader& pkbReader) override;
//  IntermediateTable evaluateConstantValue(PKBReader& pkbReader) override;
//  IntermediateTable evaluateProcName(PKBReader& pkbReader) override;
//  IntermediateTable evaluateVarName(PKBReader& pkbReader) override;
//  IntermediateTable evaluateCallProcName(PKBReader& pkbReader) override;
//  IntermediateTable evaluateCallStmtNum(PKBReader& pkbReader) override;
//  IntermediateTable evaluateReadVarName(PKBReader& pkbReader) override;
//  IntermediateTable evaluateReadStmtNum(PKBReader& pkbReader) override;
//  IntermediateTable evaluatePrintVarName(PKBReader& pkbReader) override;
//  IntermediateTable evaluatePrintStmtNum(PKBReader& pkbReader) override;
//
// public:
//  explicit DoubleSynWithEvaluator(unique_ptr<SynonymArg> firstArg,
//                                  unique_ptr<SynonymArg> secondArg)
//      : firstSynonymArg(move(firstArg)), secondSynonymArg(move(secondArg)) {};
//
//  IntermediateTable evaluate(PKBReader& pkbReader) override;
//};