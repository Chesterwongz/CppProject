#pragma once

#include <memory>

#include "qps/token/PQLToken.h"

class PQLTokenStream {
private:
	int currIndex;
	int tokenListSize;
	unique_ptr<TokenPtrList> tokenList;

public:
	explicit PQLTokenStream(unique_ptr<TokenPtrList> tokenList);
	const bool isTokenStreamEnd();
	void next();
    PQLToken& getCurrentToken();
    PQLToken& peek();
};

