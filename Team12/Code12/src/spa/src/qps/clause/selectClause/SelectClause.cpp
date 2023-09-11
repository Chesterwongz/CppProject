#include "SelectClause.h"

#include <utility>
#include <algorithm>
#include "../utils/ClauseConstants.h"

SelectClause::SelectClause(Synonym synonym) : synonym(std::move(synonym)) {}

std::unordered_set<int> SelectClause::evaluate(Context context, PKBReader *pkb) {
	Entity entity = context.getTokenEntity(synonym);
	std::string stmtType = EntityToStatementType.at(entity);

	std::set<int> results = pkb->selectStatement(stmtType);

	return results;
}
