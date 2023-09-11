#include "DeclarativeTokenFactory.h"
#include "qps/token/declarativeToken/DeclarativeToken.h"

// TODO: Tokenizer to try to ensure keyword/entity is a single element at index 0.
// e.g. "stmt s1, s2" --> ["stmt", "s1", "s2"]
// e.g. "procedure call c" --> ["procedure call", "c"]
const bool DeclarativeTokenFactory::isValid(UnvalidatedTokens unvalidatedTokens) {
	for (size_t i = 1; i < unvalidatedTokens.size(); i++)
	{
		bool res = TokenFactory::isSynonym(unvalidatedTokens[i]);
		if (!res) return false;
	}

	return true;
}

void DeclarativeTokenFactory::setEntityType(string entity) {
    entityType = entity;
}

TokenStreamPtr DeclarativeTokenFactory::createTokens(UnvalidatedTokens unvalidatedTokens) {
    if (!isValid(unvalidatedTokens)) {
        throw std::runtime_error("Declarative token stream is invalid");
    }

    if (unvalidatedTokens.empty()) {
        return std::make_unique<std::vector<std::unique_ptr<QueryToken>>>();
    }

    TokenStreamPtr declarativeTokens = std::make_unique<std::vector<std::unique_ptr<QueryToken>>>();

    for (size_t i = 1; i < unvalidatedTokens.size(); i++)
    {
        auto token = std::make_unique<DeclarativeToken>(entityType, unvalidatedTokens[i]);
        declarativeTokens->push_back(std::move(token));
    }

    return declarativeTokens;
}
