#include "SelectClause.h"

#include <utility>
#include <unordered_set>
#include "../utils/ClauseConstants.h"

SelectClause::SelectClause(Synonym synonym) : synonym(synonym) {}

std::unordered_set<int> SelectClause::evaluate(Context context, PKBReader *pkb) {
	Entity entity = context.getTokenEntity(synonym);
	std::string stmtType = EntityToStatementType.at(entity);

	std::unordered_set<int> results = pkb->getStatement(stmtType);

	return results;
}
