#include "PQLTokenizer.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/common/PQLParserUtils.h"
#include "qps/common/QPSStringUtils.h"

PQLTokenizer::PQLTokenizer(const string& query) :
	tokenList(make_unique<PQLTokenList>()),
    currPos(0),
	tokenTable(),
    query(query),
    isProcessingLiteral(false),
    numberOfTokensInLiteral(0)
{
    buffer.reserve(BUFFER_SIZE);
    literalBuffer.reserve(BUFFER_SIZE);
}

// TODO: can be converted to a mix of strategy pattern and simple methods for complex edges and simpler cases respectively
unique_ptr<PQLTokenList> PQLTokenizer::tokenize() {
	while (currPos < query.length()) {
        PQLTokenType currType = tokenTable.getTokenType(query.at(currPos));

        // will only check the first char in buffer
        switch (currType) {
            case PQL_CHAR_TOKEN:
                processName();
                break;
            case PQL_INTEGER_TOKEN:
                processInt();
                break;
            case PQL_QUOTE_TOKEN:
                processLiteral();
                break;
            case PQL_WILDCARD_TOKEN:
            case PQL_ASTERISKS_TOKEN:
            case PQL_SEMICOLON_TOKEN:
            case PQL_COMMA_TOKEN:
            case PQL_OPEN_BRACKET_TOKEN:
            case PQL_CLOSE_BRACKET_TOKEN:
            case PQL_OPERATOR_TOKEN:
                processSymbols(currType);
                break;
            case PQL_IGNORE_TOKEN:
                currPos++;
                break;
            case PQL_INVALID_TOKEN:
            default:
                throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_INVALID_TOKEN);
        }
    }

    if (isProcessingLiteral) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNMATCHED_QUOTE);
    }

    return std::move(tokenList);
}

void PQLTokenizer::flushBuffer(PQLTokenType type) {
    if (buffer.empty()) {
        return;
    }
    if (!isProcessingLiteral) {
        tokenList->push_back(PQLToken(type, buffer));
    } else {
        literalBuffer.append(buffer);
        literalBuffer += ' ';
    }
    buffer.clear();
}

void PQLTokenizer::flushLiteralBuffer(PQLTokenType type) {
    if (literalBuffer.empty()) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_EMPTY_LITERAL);
    }
    tokenList->push_back(PQLToken(type, literalBuffer));
    literalBuffer.clear();
}

// Refactor processName() and processInt() due to similarities
void PQLTokenizer::processName() {
    while (currPos < query.length()) {
        char c = query.at(currPos);

        PQLTokenType currType = tokenTable.getTokenType(c);
        if (PQLParserUtils::isDelimiter(currType)) {
            break;
        }
        buffer.push_back(c);
        currPos++;
    }
    if (!QPSStringUtils::isSynonym(buffer)) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_INAVLID_NAME);
    }
    if (isProcessingLiteral) numberOfTokensInLiteral++;
    flushBuffer(PQL_NAME_TOKEN);
}

void PQLTokenizer::processInt() {
    while (currPos < query.length()) {
        char c = query.at(currPos);
        PQLTokenType currType = tokenTable.getTokenType(c);
        if (PQLParserUtils::isDelimiter(currType)) {
            break;
        }
        buffer.push_back(c);
        currPos++;
    }
    if (!QPSStringUtils::isInteger(buffer)) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_INAVLID_INTEGER);
    }
    if (isProcessingLiteral) numberOfTokensInLiteral++;
    flushBuffer(PQL_INTEGER_TOKEN);
}

void PQLTokenizer::processLiteral() {
    // currPos is a quote
    isProcessingLiteral = !isProcessingLiteral;
    currPos++;

    if (!isProcessingLiteral) {
        PQLTokenType type = numberOfTokensInLiteral == 1
                ? PQL_LITERAL_REF_TOKEN
                : PQL_LITERAL_EXPRESSION_TOKEN;
        flushLiteralBuffer(type);
    }
}

void PQLTokenizer::processSymbols(const PQLTokenType type) {
    buffer.push_back(query.at(currPos));
    flushBuffer(type);
    currPos++;
}
