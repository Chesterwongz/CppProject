#pragma once

#include "IParserState.h"
#include "qps/common/PQLParserUtils.h"
#include "qps/query/Query.h"
#include "qps/context/Context.h"
#include "qps/tokenizer/tokenStream/PQLTokenStream.h"
#include "qps/clause/Clause.h"

class PQLParserContext {
private:
	Query& query; // belongs to driver
	unique_ptr<Context> context;
	PQLTokenStream& tokenStream; // token stream belongs to driver
	unique_ptr<IParserState> currState;
	
public:
	explicit PQLParserContext(
		PQLTokenStream& tokenStream,
		Query& query
	);
	void addToContext(string entity, string synonym);
    string getSynonymType(const string &synonym);
	[[nodiscard]] PQLTokenStream& getTokenStream() const;
	void transitionTo(unique_ptr<IParserState> nextState);
    void addClause(unique_ptr<Clause> clause);
    void handleTokens();
};
