#include "BaseAbstraction.h"

BaseAbstraction::BaseAbstraction(AbstractionParams &params)
    : pkb(params.pkb),
      abstraction(params.abstraction),
      firstArg(params.firstArg),
      secondArg(params.secondArg),
      firstArgValue(params.firstArg.getValue()),
      secondArgValue(params.secondArg.getValue()),
      argumentPermutation(getPermutation(params.firstArg, params.secondArg)) {}

StmtType BaseAbstraction::getFirstArgStmtType() {
  return getArgStmtType(this->firstArg);
}

StmtType BaseAbstraction::getSecondArgStmtType() {
  return getArgStmtType(this->secondArg);
}

IntermediateTable BaseAbstraction::evaluate() {
  return argumentPermutationToEvalMap[this->argumentPermutation](*this);
}

/**
 * Template methods for each permutation of argument.
 * Classes implementing BaseAbstraction will only implement
 * the relevant methods applicable to its type.
 * @return IntermediateTable query results
 */

// Abstraction (Synonym, Synonym)
IntermediateTable BaseAbstraction::evaluateSynonymSynonym() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Synonym, Integer)
IntermediateTable BaseAbstraction::evaluateSynonymInteger() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Synonym, Identifier)
IntermediateTable BaseAbstraction::evaluateSynonymIdent() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Synonym, _)
IntermediateTable BaseAbstraction::evaluateSynonymWildcard() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Integer, Synonym)
IntermediateTable BaseAbstraction::evaluateIntegerSynonym() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Integer, Integer)
IntermediateTable BaseAbstraction::evaluateIntegerInteger() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Integer, Identifier)
IntermediateTable BaseAbstraction::evaluateIntegerIdent() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Integer, _)
IntermediateTable BaseAbstraction::evaluateIntegerWildcard() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Identifier, Synonym)
IntermediateTable BaseAbstraction::evaluateIdentSynonym() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Identifier, Integer)
IntermediateTable BaseAbstraction::evaluateIdentInteger() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Identifier, Identifier)
IntermediateTable BaseAbstraction::evaluateIdentIdent() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Identifier, _)
IntermediateTable BaseAbstraction::evaluateIdentWildcard() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (_, Synonym)
IntermediateTable BaseAbstraction::evaluateWildcardSynonym() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (_, Identifier)
IntermediateTable BaseAbstraction::evaluateWildcardIdent() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (_, Integer)
IntermediateTable BaseAbstraction::evaluateWildcardInteger() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (_, _)
IntermediateTable BaseAbstraction::evaluateWildcardWildcard() {
  throw QPSInvalidAbstractionException(
      QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}
