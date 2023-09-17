#pragma once

#include <string>
#include <vector>
#include <memory>

#include "qps/tokenizer/PQLTokenType.h"

using std::string, std::vector, std::unique_ptr;

typedef string TokenValue;

class PQLToken {
private:
	PQLTokenType type;
	TokenValue value;

protected:
	explicit PQLToken(PQLTokenType type);
	PQLToken(PQLTokenType type, const TokenValue value);

public:
	PQLTokenType getType() const;
	TokenValue getValue() const;
};

typedef vector<unique_ptr<PQLToken>> TokenPtrList;
