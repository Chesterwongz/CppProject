#include "IAbstraction.h"

IAbstraction::IAbstraction(AbstractionParams &params) :
        pkb(params.pkb),
        context(params.context),
        abstraction(params.abstraction),
        firstArg(params.firstArg),
        secondArg(params.secondArg),
        firstArgValue(params.firstArg.getValue()),
        secondArgValue(params.secondArg.getValue()),
        argumentPermutation(getPermutation(params.firstArg,
                                           params.secondArg)),
        isTransitive(params.isTransitive) {};

ArgumentPermutation IAbstraction::getAbstractionPermutation() {
    return this->argumentPermutation;
}

StmtType IAbstraction::getFirstArgStmtType() {
    if (this->firstArg.isSynonym()) {
        Entity firstStmtEntity = this->context.getTokenEntity(this->firstArgValue);
        return EntityToStatementType.at(firstStmtEntity);
    } else if (this->firstArg.isWildcard()) {
        return StmtType::STMT;
    }
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_NON_STATEMENT_TYPE);
}

StmtType IAbstraction::getSecondArgStmtType() {
    if (this->secondArg.isSynonym()) {
        Entity secondStmtEntity = this->context.getTokenEntity(this->secondArgValue);
        return EntityToStatementType.at(secondStmtEntity);
    } else if (this->secondArg.isWildcard()) {
        return StmtType::STMT;
    }
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_NON_STATEMENT_TYPE);
}

/**
 * Template methods for each permutation of argument.
 * Classes implementing IAbstraction will only implement
 * the relevant methods applicable to its type.
 * @return IntermediateTable query results
 */

// Abstraction (Synonym, Synonym)
IntermediateTable IAbstraction::evaluateSynonymSynonym() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Synonym, Integer)
IntermediateTable IAbstraction::evaluateSynonymInteger() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Synonym, Identifier)
IntermediateTable IAbstraction::evaluateSynonymIdent() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Synonym, _)
IntermediateTable IAbstraction::evaluateSynonymWildcard() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}


// Abstraction (Integer, Synonym)
IntermediateTable IAbstraction::evaluateIntegerSynonym() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Integer, Integer)
IntermediateTable IAbstraction::evaluateIntegerInteger() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Integer, Identifier)
IntermediateTable IAbstraction::evaluateIntegerIdent() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Integer, _)
IntermediateTable IAbstraction::evaluateIntegerWildcard() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}


// Abstraction (Identifier, Synonym)
IntermediateTable IAbstraction::evaluateIdentSynonym() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Identifier, Integer)
IntermediateTable IAbstraction::evaluateIdentInteger() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Identifier, Identifier)
IntermediateTable IAbstraction::evaluateIdentIdent() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (Identifier, _)
IntermediateTable IAbstraction::evaluateIdentWildcard() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}


// Abstraction (_, Synonym)
IntermediateTable IAbstraction::evaluateWildcardSynonym() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (_, Identifier)
IntermediateTable IAbstraction::evaluateWildcardIdent() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (_, Integer)
IntermediateTable IAbstraction::evaluateWildcardInteger() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}

// Abstraction (_, _)
IntermediateTable IAbstraction::evaluateWildcardWildcard() {
    throw QPSInvalidAbstractionException(QPS_INVALID_ABSTRACTION_ERR_UNSUPPORTED_ARG_TYPE);
}
