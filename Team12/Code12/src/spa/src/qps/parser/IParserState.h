#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "qps/token/PQLToken.h"

using std::unique_ptr, std::unordered_map, std::unordered_set;

typedef unordered_map<PQLTokenType, unordered_set<PQLTokenType>> PredictiveMap;

class IParserState {
private:
	// e.g. check if the next token is correct type
	virtual bool isExpectedToken(PQLTokenType currType) = 0;
public:
	virtual void handleToken() = 0;
};
