#include "PQLParserContext.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

PQLParserContext::PQLParserContext(
	unique_ptr<PQLTokenStream>& tokenStream,
	unique_ptr<IParserState> currState,
	unique_ptr<Query>& query) {

	this->tokenStream = tokenStream;
	this->currState = currState;
	this->query = query;
	this->context = Context();
}

unique_ptr<PQLToken>& PQLParserContext::lookAhead() const
{
	auto next = tokenStream->peek();

	if (next == nullptr) {
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);
	}

	return next;
}

unique_ptr<PQLTokenStream>& PQLParserContext::getTokenStream() const
{
	return tokenStream;
}

void PQLParserContext::transitionTo(unique_ptr<IParserState> nextState)
{
	currState = nextState;
}
