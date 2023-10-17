#include "UsesAbstraction.h"

/**
 * Uses abstraction:
 * - firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * - secondArg: Synonym OR Identifier OR Wildcard
 */

UsesAbstraction::UsesAbstraction(AbstractionParams abstractionParams)
    : StmtOrProcToVarAbstraction(abstractionParams,
                                 &PKBReader::getAllUsedVariables,
                                 &PKBReader::getUsesProcPairs,
                                 &PKBReader::getStatementsUsing,
                                 &PKBReader::getProcUsing,
                                 &PKBReader::getVariablesUsedBy,
                                 &PKBReader::getVarsUsedByProc,
                                 &PKBReader::isVariableUsedBy,
                                 &PKBReader::isVariableUsedByProc) {}
