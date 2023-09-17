#pragma once

#include <memory>

#include "qps/token/PQLToken.h"

using std::unique_ptr;

class IParserState {
private:
	// e.g. check if the next token is correct type
	virtual bool isExpectedToken(PQLTokenType currType) = 0;
public:
	virtual void handleToken(PQLTokenType tokenType) = 0;
};
