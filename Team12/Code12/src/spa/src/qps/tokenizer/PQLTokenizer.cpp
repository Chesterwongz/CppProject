#include "PQLTokenizer.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/common/PQLParserUtils.h"

PQLTokenizer::PQLTokenizer() {
	buffer("");
	tokenList({});
	processingLiteral(false);
	containsChar(false);
	tokenTable();
}

unique_ptr<PQLTokenStream> PQLTokenizer::tokenize(const string& query) {
	for (size_t pos = 0; pos < query.size(); pos++) {
		char c = query.at(pos);
		processChar(c);
	}

	if (processingLiteral) {
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNMATCHED_QUOTE);
	}

	return make_unique<PQLTokenStream>(tokenList);
}

void PQLTokenizer::processChar(const char c) {
	PQLTokenType type = tokenTable->getTokenType(c);

	switch (type) {

	case PQL_INVALID_TOKEN:
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);

	case PQL_CHAR_TOKEN:
		containsChar = true;
	case PQL_INTEGER_TOKEN:
		buffer.push_back(c);
		return;

	case PQL_SEMICOLON_TOKEN:
	case PQL_COMMA_TOKEN:
	case PQL_IGNORE_TOKEN:
		break;

	case PQL_QUOTE_TOKEN:
		toggleLiteral();
		return;

	// all other tokens should be appended as an individual token
	default:
		break;
	}

	flushBuffer();
}

void PQLTokenizer::toggleLiteral() {
	processChar = !processChar;
}

void PQLTokenizer::flushBuffer() {
	if (buffer.length() > 0) {
		if (!containsChar && PQLParserUtils::isValidInteger(buffer)) {
			tokenList->push_back(make_unique<PQLToken>(PQL_INTEGER_TOKEN, buffer));
		}
		else if (PQLParserUtils::isValidName(buffer)) {
			tokenList->push_back(make_unique<PQLToken>(PQL_NAME_TOKEN, buffer));
		}

		buffer.clear();
		containsChar = false;
	}
}

