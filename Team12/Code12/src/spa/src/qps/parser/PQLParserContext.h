#pragma once

#include "IParserState.h"
#include "qps/common/PQLParserUtils.h"
#include "qps/query/Query.h"
#include "qps/context/Context.h"
#include "qps/tokenizer/tokenStream/PQLTokenStream.h"

// here context refers to the context in state pattern
// replaces the QueryBuilder and TokenFactory
class PQLParserContext {
private:
	unique_ptr<Query>& query; // belongs to driver
	unique_ptr<Context> context;
	unique_ptr<PQLTokenStream>& tokenStream; // token stream belongs to driver
	unique_ptr<IParserState> currState;
	
public:
	explicit PQLParserContext(
		unique_ptr<PQLTokenStream>& tokenStream, 
		unique_ptr<IParserState> currState,
		unique_ptr<Query>& query
	);
	void addToContext(string entity, string synonym);
	unique_ptr<PQLTokenStream>& getTokenStream() const;
	void transitionTo(unique_ptr<IParserState> nextState);
};
