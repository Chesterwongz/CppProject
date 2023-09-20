#include "PQLTokenStream.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

PQLTokenStream::PQLTokenStream(unique_ptr<PQLTokenList> tokenList) :
	tokenList(std::move(tokenList))
{
	currIndex = 0;
	tokenListSize = tokenList->size();
}

const bool PQLTokenStream::isTokenStreamEnd() {
	return currIndex >= tokenListSize;
}

void PQLTokenStream::next() {
	if (!isTokenStreamEnd()) {
		currIndex++;
	}
}

PQLToken& PQLTokenStream::peek() {
	if (!isTokenStreamEnd()) {
		return tokenList->at(currIndex);
	}
    throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_OUT_OF_BOUNDS);
}

PQLToken& PQLTokenStream::getCurrentToken() {
	if (isTokenStreamEnd()) {
        throw QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_OUT_OF_BOUNDS);
    }

	return tokenList->at(currIndex);
}
