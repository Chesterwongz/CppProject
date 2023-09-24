#include "FollowsAbstraction.h"

 IntermediateTable FollowsAbstraction::getAbstractions() {
     bool isFirstStmtSynonym = firstArg.isSynonym();
     bool isSecondStmtSynonym = secondArg.isSynonym();

     string firstArgValue = firstArg.getValue();
     StmtType firstStmtType = isFirstStmtSynonym ?
                              EntityToStatementType.at(context.getTokenEntity(firstArgValue))
                                                 : StmtType::STMT;
     string secondArgValue = secondArg.getValue();
     StmtType secondStmtType = isSecondStmtSynonym ?
                              EntityToStatementType.at(context.getTokenEntity(secondArgValue))
                                                 : StmtType::STMT;

     vector<pair<string, string>> statementsModifyingVar = this->isTransitive ?
             pkb.getFollowsStarPairs(firstStmtType, secondStmtType)
             : pkb.getFollowsPairs(firstStmtType, secondStmtType);

     return IntermediateTableFactory::buildIntermediateTable(
             firstArgValue,
             secondArgValue,
             statementsModifyingVar);
 }
