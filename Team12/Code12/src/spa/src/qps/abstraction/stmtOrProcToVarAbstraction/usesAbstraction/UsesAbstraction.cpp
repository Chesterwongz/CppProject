#include "UsesAbstraction.h"

/**
 * Uses abstraction:
 * - firstArg: Synonym OR Integer (stmt) OR Identifier (Proc)
 * - secondArg: Synonym OR Identifier OR Wildcard
 */

UsesAbstraction::UsesAbstraction(AbstractionParams abstractionParams)
    : StmtOrProcToVarAbstraction(abstractionParams,
                                 &PKBReader::getAllUsedVariables,
                                 &PKBReader::getAllUsedVariablesByProcs,
                                 &PKBReader::getStatementsUsing,
                                 &PKBReader::getProceduresUsing,
                                 &PKBReader::getVariablesUsedBy,
                                 &PKBReader::getUsedVariablesForProc,
                                 &PKBReader::isVariableUsedBy,
                                 &PKBReader::isVariableUsedByProc) {}
