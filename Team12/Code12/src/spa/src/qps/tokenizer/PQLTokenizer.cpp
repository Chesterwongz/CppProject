#include "PQLTokenizer.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/common/PQLParserUtils.h"

PQLTokenizer::PQLTokenizer() {
	buffer("");
	literalBuffer("");
	tokenList(make_unique<TokenPtrList>());
	processingLiteral(false);
	containsChar(false);
	tokenTable();
	// TODO: Reserve buffer size
}

unique_ptr<PQLTokenStream> PQLTokenizer::tokenize(const string& query) {
	for (size_t pos = 0; pos < query.size(); pos++) {
		char c = query.at(pos);
		processChar(c);
	}

	if (processingLiteral) {
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNMATCHED_QUOTE);
	}

	return make_unique<PQLTokenStream>(move(tokenList));
}

void PQLTokenizer::processChar(const char c) {
	PQLTokenType type = tokenTable->getTokenType(c);

	switch (type) {

	case PQL_INVALID_TOKEN:
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);

	case PQL_CHAR_TOKEN:
		containsChar = true;
	case PQL_INTEGER_TOKEN:
	if (!processingLiteral) {
		buffer.push_back(c);
	}
	else {
		literalBuffer.push_back(c);
	}
		return;

	// these tokens are delimiters
	case PQL_SEMICOLON_TOKEN:
	case PQL_COMMA_TOKEN:
	case PQL_IGNORE_TOKEN:
		flushBuffer();
		return;

	case PQL_QUOTE_TOKEN:
		toggleLiteral();
		return;

	// all other tokens should be appended as an individual token
	default:
		break;
	}

	flushBuffer();
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

void PQLTokenizer::toggleLiteral() {
	if (!processingLiteral) {
		startLiteral();
	}
	else {
		endLiteral();
	}
}

void PQLTokenizer::startLiteral() {
	literalBuffer.clear();
	processingLiteral = true;
	literalSymbolCount = 0;
}

void PQLTokenizer::endLiteral() {
	flushBuffer();
	processingLiteral = false;

	if (literalBuffer.empty()) {
		throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_EMPTY_LITERAL);
	}

	tokenList->push_back(PQLToken(PQL_LITERAL_TOKEN, literalBuffer));

	literalBuffer.clear();
}
