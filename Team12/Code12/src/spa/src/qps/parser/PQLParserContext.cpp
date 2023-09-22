#include "PQLParserContext.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

PQLParserContext::PQLParserContext(
	PQLTokenStream& tokenStream,
	Query& query) :
	tokenStream(tokenStream),
	query(query),
    currState(),
	context(std::make_unique<Context>()) {}

PQLTokenStream& PQLParserContext::getTokenStream() const
{
	return tokenStream;
}

void PQLParserContext::transitionTo(unique_ptr<IParserState> nextState)
{
	currState = std::move(nextState);
    currState->handleToken();
}

void PQLParserContext::addToContext(string entity, string synonym) {
	if (!PQLParserUtils::isSynonym(synonym)) {
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_SYNONYM);
	}
	this->context->addSynonym(synonym, entity);
}

void PQLParserContext::addClause(unique_ptr<Clause> clause) {
    query.addClause(std::move(clause));
}

string PQLParserContext::getSynonymType(const string &synonym) {
    return this->context->getTokenEntity(synonym);
}
