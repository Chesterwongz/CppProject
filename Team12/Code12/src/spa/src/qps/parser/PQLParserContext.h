#pragma once

#include "IParserState.h"
#include "qps/tokenizer/tokenStream/PQLTokenStream.h"
#include "qps/queryBuilder/QueryBuilder.h"

// here context refers to the context in state pattern
class PQLParserContext {
private:
	unique_ptr<QueryBuilder>& queryBuilder;
	unique_ptr<PQLTokenStream>& tokenStream; // token stream belongs to driver
	
pulbic:
	unique_ptr<PQLTokenStream>& getTokenStream();
};
