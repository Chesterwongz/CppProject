#include "DeclarativeTokenFactory.h"
#include "../../token/declarativeToken/DeclarativeToken.h"

// TODO: Tokenizer to try to ensure keyword/entity is a single element at index 0.
// e.g. "stmt s1, s2" --> ["stmt", "s1", "s2"]
// e.g. "procedure call c" --> ["procedure call", "c"]

const bool DeclarativeTokenFactory::isValid(UnvalidatedTokens unvalidatedTokens) {
	// data should have been processed properly. TokenFactory should only validate + create tokens.
	// e.g. "stmt s1, s2, s3;" --> ["stmt", "s1", "s2", "s3"]
	for (size_t i = 1; i < unvalidatedTokens.size; i++)
	{
		bool res = TokenFactory::isSynonym(s);
		if (!res) return false;
	}

	return true;
}

TokenStreamPtr DeclarativeTokenFactory::createTokens(ValidatedTokens validatedTokens) {
	string entityType = validatedTokens[0];
	TokenStreamPtr declarativeTokens = std::make_unique<vector<DeclarativeToken>>();

	for (size_t i = 1; i < validatedTokens.size; i++)
	{
		DeclarativeToken token(entityType, validatedTokens[i]);
		declarativeTokens->push_back(token);
	}

	return declarativeTokens;
}





