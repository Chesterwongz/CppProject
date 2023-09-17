#include "qps/query/Query.h"
#include "pkb/facade/PKB.h"
#include "QueryBuilder.h"

QueryBuilder::QueryBuilder(auto pkb) : pkb(pkb) {
	this->query = Query(pkb);
}

unique_ptr<Query> QueryBuilder::buildQuery() {
	for (int i = 0; i < clauses.size(); i++)
	{
		query->addClause(move(clauses[i]));
	}
	query->addContext(move(context));
	return move(query);
}

void QueryBuilder::addSynonym(string name, string entity) {
	context->addToken(name, entity);
}

string QueryBuilder::isExistingSynonym(string synonym) {
	return context->getTokenEntitygetTokenEntity(synonym);
}
