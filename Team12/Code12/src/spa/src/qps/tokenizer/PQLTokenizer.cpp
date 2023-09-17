#include "PQLTokenizer.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

PQLTokenizer::PQLTokenizer() {
	buffer("");
	tokenList({});
	processingLiteral(false);
	processingArgument(false);
	tokenTable();
	currType(PQL_NULL_TOKEN);
}

unique_ptr<PQLTokenStream> PQLTokenizer::tokenize(const string& query) {
	for (size_t pos = 0; pos < query.size(); pos++) {
		char c = query.at(pos);
		processChar(c);
	}

	if (processingLiteral) {
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNMATCHED_QUOTE);
	}

	if (processingArgument) {
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNMATCHED_BRACKET);
	}

	return make_unique<PQLTokenStream>(tokenList);
}

void PQLTokenizer::processChar(const char c) {
	PQLTokenType type = tokenTable->getTokenType(c);

	if (currType == PQL_NULL_TOKEN) { // means the first char in token
		currType = type;
	}

	// TODO: Incomplete
	switch (type) {
	case PQL_SEMICOLON_TOKEN:
	case PQL_COMMA_TOKEN:
		auto newToken = make_unique<PQLToken>(type);
		// intended to fall through
	case PQL_IGNORE_TOKEN:
		flushBuffer();
		break;
	case PQL_NAME_TOKEN:
	case PQL_INTEGER_TOKEN:
		break;
	case PQL_WILDCARD_TOKEN:
		break;
	case PQL_PERIOD_TOKEN:
		break;
	case PQL_ASTERICKS_TOKEN:
		break;
	case PQL_OPEN_BRACKET_TOKEN: 
		break;
	case PQL_CLOSE_BRACKET_TOKEN:
		break;
	case PQL_QUOTE_TOKEN:
		break;
	case PQL_OPERATOR_TOKEN:
		break;
	case PQL_INVALID_TOKEN:
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);
		break;
	default:
		break;
	}
}

void PQLTokenizer::toggleLiteral() {
	processChar = !processChar;
}

void PQLTokenizer::appendToken()

void PQLTokenizer::flushBuffer() {
	buffer = "";
	currType = PQL_NULL_TOKEN;
}

