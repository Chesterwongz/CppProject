#include "qps/query/Query.h"
#include "pkb/facade/PKB.h"
#include "QueryBuilder.h"

QueryBuilder::QueryBuilder(PKBReader& pkb) : pkb(pkb) {
	this->query(pkb);
}

unique_ptr<Query> QueryBuilder::buildQuery() {
	for (int i = 0; i < clauses.size(); i++)
	{
		query->addClause(std::move(clauses[i]));
	}
	query->addContext(std::move(context));
	return move(query);
}

void QueryBuilder::addSynonym(string name, string entity) {
	context.addToken(name, entity);
}

string QueryBuilder::isExistingSynonym(string synonym) {
	return context.getTokenEntity(synonym);
}
