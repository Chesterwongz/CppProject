#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "AbstractionUtils.h"
#include "pkb/facade/PKB.h"
#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/clause/utils/ClauseConstants.h"
#include "qps/intermediateTable/IntermediateTable.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/query/Query.h"

class BaseAbstraction {
 private:
  virtual bool isFirstSynonymInvalid() = 0;
  virtual bool isSecondSynonymInvalid() = 0;
  static ClauseSignature getClauseAbstractionSignature(
      const Abstraction& abstraction, AbstractArgument& firstArg,
      AbstractArgument& secondArg);

 protected:
  PKBReader& pkb;
  Abstraction abstraction;
  AbstractArgument& firstArg;
  AbstractArgument& secondArg;
  string firstArgValue;
  string secondArgValue;
  ArgumentPermutation argumentPermutation;

  explicit BaseAbstraction(AbstractionParams& params);

  StmtType getFirstArgStmtType();
  StmtType getSecondArgStmtType();

  ClauseSignature signature;

 public:
  virtual ~BaseAbstraction() = default;
  IntermediateTable evaluate();

  virtual IntermediateTable evaluateSynonymSynonym();
  virtual IntermediateTable evaluateSynonymInteger();
  virtual IntermediateTable evaluateSynonymIdent();
  virtual IntermediateTable evaluateSynonymWildcard();

  virtual IntermediateTable evaluateIntegerSynonym();
  virtual IntermediateTable evaluateIntegerInteger();
  virtual IntermediateTable evaluateIntegerIdent();
  virtual IntermediateTable evaluateIntegerWildcard();

  virtual IntermediateTable evaluateIdentSynonym();
  virtual IntermediateTable evaluateIdentInteger();
  virtual IntermediateTable evaluateIdentIdent();
  virtual IntermediateTable evaluateIdentWildcard();

  virtual IntermediateTable evaluateWildcardSynonym();
  virtual IntermediateTable evaluateWildcardInteger();
  virtual IntermediateTable evaluateWildcardIdent();
  virtual IntermediateTable evaluateWildcardWildcard();
};

typedef std::function<IntermediateTable(BaseAbstraction&)>
    AbstractionEvaluatorFunc;
inline unordered_map<ArgumentPermutation, AbstractionEvaluatorFunc>
    argumentPermutationToEvalMap = {
        {ArgumentPermutation::SYNONYM_SYNONYM,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateSynonymSynonym();
         }},
        {ArgumentPermutation::SYNONYM_INTEGER,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateSynonymInteger();
         }},
        {ArgumentPermutation::SYNONYM_IDENT,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateSynonymIdent();
         }},
        {ArgumentPermutation::SYNONYM_WILDCARD,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateSynonymWildcard();
         }},
        {ArgumentPermutation::INTEGER_SYNONYM,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateIntegerSynonym();
         }},
        {ArgumentPermutation::INTEGER_INTEGER,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateIntegerInteger();
         }},
        {ArgumentPermutation::INTEGER_IDENT,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateIntegerIdent();
         }},
        {ArgumentPermutation::INTEGER_WILDCARD,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateIntegerWildcard();
         }},
        {ArgumentPermutation::IDENT_SYNONYM,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateIdentSynonym();
         }},
        {ArgumentPermutation::IDENT_INTEGER,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateIdentInteger();
         }},
        {ArgumentPermutation::IDENT_IDENT,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateIdentIdent();
         }},
        {ArgumentPermutation::IDENT_WILDCARD,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateIdentWildcard();
         }},
        {ArgumentPermutation::WILDCARD_SYNONYM,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateWildcardSynonym();
         }},
        {ArgumentPermutation::WILDCARD_INTEGER,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateWildcardInteger();
         }},
        {ArgumentPermutation::WILDCARD_IDENT,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateWildcardIdent();
         }},
        {ArgumentPermutation::WILDCARD_WILDCARD,
         [](BaseAbstraction& abstraction) {
           return abstraction.evaluateWildcardWildcard();
         }},
};
