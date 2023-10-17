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
                                 &PKBReader::getAllModifiedVariablesByProcs,
                                 &PKBReader::getStatementsModifying,
                                 &PKBReader::getProceduresModifying,
                                 &PKBReader::getVariablesModifiedBy,
                                 &PKBReader::getModifiedVariablesForProc,
                                 &PKBReader::isVariableModifiedBy,
                                 &PKBReader::isVariableModifiedByProc) {}
