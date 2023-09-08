#include "DeclarativeTokenFactory.h"
#include "qps/token/declarativeToken/DeclarativeToken.h"

// TODO: Tokenizer to try to ensure keyword/entity is a single element at index 0.
// e.g. "stmt s1, s2" --> ["stmt", "s1", "s2"]
// e.g. "procedure call c" --> ["procedure call", "c"]

const bool DeclarativeTokenFactory::isValid(UnvalidatedTokens unvalidatedTokens) {
	// data should have been processed properly. TokenFactory should only validate + create tokens.
	// e.g. "stmt s1, s2, s3;" --> ["stmt", "s1", "s2", "s3"]
	for (size_t i = 1; i < unvalidatedTokens.size(); i++)
	{
		bool res = TokenFactory::isSynonym(unvalidatedTokens[i]);
		if (!res) return false;
	}

	return true;
}

TokenStreamPtr DeclarativeTokenFactory::createTokens(ValidatedTokens validatedTokens) {
    if (validatedTokens.empty()) {
        return std::make_unique<std::vector<std::unique_ptr<QueryToken>>>();
    }

    string entityType = validatedTokens[0];
    TokenStreamPtr declarativeTokens = std::make_unique<std::vector<std::unique_ptr<QueryToken>>>();

    for (size_t i = 1; i < validatedTokens.size(); i++)
    {
        auto token = std::make_unique<DeclarativeToken>(entityType, validatedTokens[i]);
        declarativeTokens->push_back(std::move(token));
    }

    return declarativeTokens;
}
