#pragma once

#include <memory>
#include <vector>
#include <string>

#include "qps/tokenFactory/TokenFactory.h"

using std::unique_ptr, std::vector, std::string;

class DeclarativeTokenFactory : public TokenFactory {
protected:
	const bool isValid(UnvalidatedTokens unvalidatedTokens) override;

public:
	explicit DeclarativeTokenFactory() : TokenFactory() {}
	TokenStreamPtr createTokens(ValidatedTokens validatedTokens) override;
};
