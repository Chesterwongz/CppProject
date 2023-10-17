#include "ModifiesAbstraction.h"

#include <unordered_set>

/**
 * Modifies abstraction:
 * - firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * - secondArg: Synonym OR Identifier OR Wildcard
 */

ModifiesAbstraction::ModifiesAbstraction(AbstractionParams abstractionParams)
    : StmtOrProcToVarAbstraction(abstractionParams,
                                 &PKBReader::getAllModifiedVariables,
                                 &PKBReader::getModifiesProcPairs,
                                 &PKBReader::getStatementsModifying,
                                 &PKBReader::getProcModifying,
                                 &PKBReader::getVariablesModifiedBy,
                                 &PKBReader::getVarsModifiedByProc,
                                 &PKBReader::isVariableModifiedBy,
                                 &PKBReader::isVariableModifiedByProc) {}
