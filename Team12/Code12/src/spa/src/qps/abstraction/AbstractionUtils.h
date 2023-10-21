#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>

#include "common/exceptions/Exception.h"
#include "pkb/facade/PKBReader.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/utils/ClauseConstants.h"
#include "qps/exceptions/QPSInvalidAbstractionException.h"

using std::unique_ptr, std::unordered_map;

struct AbstractionParams {
  PKBReader &pkb;
  Abstraction abstraction;
  AbstractArgument &firstArg;
  AbstractArgument &secondArg;
  explicit AbstractionParams(PKBReader &pkb, Abstraction abstraction,
                             AbstractArgument &firstArg,
                             AbstractArgument &secondArg)
      : pkb(pkb),
        abstraction((abstraction)),
        firstArg(firstArg),
        secondArg(secondArg) {}
};

enum ArgumentPermutation {
  SYNONYM_SYNONYM,
  SYNONYM_INTEGER,
  SYNONYM_IDENT,
  SYNONYM_WILDCARD,

  INTEGER_SYNONYM,
  INTEGER_INTEGER,
  INTEGER_IDENT,
  INTEGER_WILDCARD,

  IDENT_SYNONYM,
  IDENT_INTEGER,
  IDENT_IDENT,
  IDENT_WILDCARD,

  WILDCARD_SYNONYM,
  WILDCARD_INTEGER,
  WILDCARD_IDENT,
  WILDCARD_WILDCARD,
};

inline unordered_map<
    QPSStringUtils::ArgumentType,
    unordered_map<QPSStringUtils::ArgumentType, ArgumentPermutation>>
    AbstractionArgumentPermutationMap = {
        {QPSStringUtils::ArgumentType::SYNONYM,
         {
             {QPSStringUtils::ArgumentType::SYNONYM,
              ArgumentPermutation::SYNONYM_SYNONYM},
             {QPSStringUtils::ArgumentType::INTEGER,
              ArgumentPermutation::SYNONYM_INTEGER},
             {QPSStringUtils::ArgumentType::IDENT,
              ArgumentPermutation::SYNONYM_IDENT},
             {QPSStringUtils::ArgumentType::WILDCARD,
              ArgumentPermutation::SYNONYM_WILDCARD},
         }},
        {QPSStringUtils::ArgumentType::INTEGER,
         {
             {QPSStringUtils::ArgumentType::SYNONYM,
              ArgumentPermutation::INTEGER_SYNONYM},
             {QPSStringUtils::ArgumentType::INTEGER,
              ArgumentPermutation::INTEGER_INTEGER},
             {QPSStringUtils::ArgumentType::IDENT,
              ArgumentPermutation::INTEGER_IDENT},
             {QPSStringUtils::ArgumentType::WILDCARD,
              ArgumentPermutation::INTEGER_WILDCARD},
         }},
        {QPSStringUtils::ArgumentType::IDENT,
         {
             {QPSStringUtils::ArgumentType::SYNONYM,
              ArgumentPermutation::IDENT_SYNONYM},
             {QPSStringUtils::ArgumentType::INTEGER,
              ArgumentPermutation::IDENT_INTEGER},
             {QPSStringUtils::ArgumentType::IDENT,
              ArgumentPermutation::IDENT_IDENT},
             {QPSStringUtils::ArgumentType::WILDCARD,
              ArgumentPermutation::IDENT_WILDCARD},
         }},
        {QPSStringUtils::ArgumentType::WILDCARD,
         {
             {QPSStringUtils::ArgumentType::SYNONYM,
              ArgumentPermutation::WILDCARD_SYNONYM},
             {QPSStringUtils::ArgumentType::INTEGER,
              ArgumentPermutation::WILDCARD_INTEGER},
             {QPSStringUtils::ArgumentType::IDENT,
              ArgumentPermutation::WILDCARD_IDENT},
             {QPSStringUtils::ArgumentType::WILDCARD,
              ArgumentPermutation::WILDCARD_WILDCARD},
         }}};

inline ArgumentPermutation getPermutation(AbstractArgument &firstArg,
                                          AbstractArgument &secondArg) {
  try {
    QPSStringUtils::ArgumentType firstArgType = firstArg.getArgumentType();
    QPSStringUtils::ArgumentType secondArgType = secondArg.getArgumentType();
    return AbstractionArgumentPermutationMap.at(firstArgType).at(secondArgType);
  } catch (Exception &e) {
    throw QPSInvalidAbstractionException(
        QPS_INVALID_ABSTRACTION_ERR_UNKNOWN_ARG_PERMUTATION);
  }
}

inline StmtType getArgStmtType(AbstractArgument &argument) {
  if (argument.isSynonym()) {
    auto &synonymArg = dynamic_cast<SynonymArg &>(argument);
    auto firstStmtEntity = synonymArg.getEntityType();
    assert(firstStmtEntity != PROCEDURE_ENTITY);
    auto entityPair = StmtEntityToStatementType.find(firstStmtEntity);
    return entityPair == StmtEntityToStatementType.end()
        ? StmtType::INVALID
        : entityPair->second;
  } else if (argument.isWildcard()) {
    return StmtType::STMT;
  }
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_NON_STATEMENT_TYPE);
}
