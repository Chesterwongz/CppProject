#include "SelectClause.h"

#include <utility>
#include <algorithm>
#include "../utils/ClauseConstants.h"

SelectClause::SelectClause(Synonym synonym) : synonym(std::move(synonym)) {}

std::set<int> SelectClause::evaluate(Context context, PKBReader pkb) {
	DeclarativeToken* selectTokenPtr = context[this->synonym];
	Entity entity = selectTokenPtr->getEntity();

	std::string stmtType = EntityToStatementType[entity];

	std::set<int> results = pkb.selectStatement(entityToUpper);

	return results;
}
