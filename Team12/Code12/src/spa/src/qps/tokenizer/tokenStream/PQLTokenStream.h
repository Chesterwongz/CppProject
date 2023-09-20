#pragma once

#include <memory>

#include "qps/token/PQLToken.h"

class PQLTokenStream {
private:
	int currIndex;
	int tokenListSize;
	unique_ptr<PQLTokenList> tokenList;

public:
	explicit PQLTokenStream(unique_ptr<PQLTokenList> tokenList);
	const bool isTokenStreamEnd();
	void next();
    PQLToken& getCurrentToken();
    PQLToken& peek();
};

