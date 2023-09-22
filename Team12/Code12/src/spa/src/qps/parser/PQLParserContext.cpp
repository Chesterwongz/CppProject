#include "PQLParserContext.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

PQLParserContext::PQLParserContext(
	PQLTokenStream& tokenStream,
	unique_ptr<IParserState> currState,
	Query& query) :

	tokenStream(tokenStream),
	currState(std::move(currState)),
	query(query),
	context(std::make_unique<Context>()) {}

PQLTokenStream& PQLParserContext::getTokenStream() const
{
	return tokenStream;
}

void PQLParserContext::transitionTo(unique_ptr<IParserState> nextState)
{
	currState = std::move(nextState);
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
