#include "PQLTokenStream.h"

PQLTokenStream::PQLTokenStream(unique_ptr<TokenPtrList> tokenList) :
	tokenList(tokenList) 
{
	currIndex = 0;
	tokenListSize = tokenList->size();
}

bool PQLTokenStream::isTokenStreamEnd() {
	return currIndex >= tokenListSize;
}

void PQLTokenStream::nextToken() {
	if (!isTokenStreamEnd) {
		currIndex++;
	}
}

unique_ptr<PQLToken>& PQLTokenStream::getCurrentToken() {
	if (isTokenStreamEnd) return nullptr;

	return tokenList->at(currIndex);
}
