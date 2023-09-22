#include <iostream>

#include "DeclarativeTokenFactory.h"
#include "qps/token/declarativeToken/DeclarativeToken.h"
#include "qps/common/QPSStringUtils.h"

// TODO: Tokenizer to try to ensure keyword/entity is a single element at index 0.
// e.g. "stmt s1, s2" --> ["stmt", "s1", "s2"]
// e.g. "procedure call c" --> ["procedure call", "c"]
bool DeclarativeTokenFactory::isValid(UnvalidatedTokens unvalidatedTokens) {
	for (size_t i = 0; i < unvalidatedTokens.size(); i++)
	{
		bool res = QPSStringUtils::isSynonym(unvalidatedTokens[i]);
		if (!res) return false;
	}

	return true;
}

void DeclarativeTokenFactory::setEntityType(string entity) {
    entityType = entity;
}

QPSTokenStreamPtr DeclarativeTokenFactory::createTokens(UnvalidatedTokens unvalidatedTokens) {
    if (!isValid(unvalidatedTokens)) {
        throw std::runtime_error("Declarative token stream is invalid");
    }

    if (unvalidatedTokens.empty()) {
        return std::make_unique<std::vector<std::unique_ptr<QueryToken>>>();
    }

    QPSTokenStreamPtr declarativeTokens = std::make_unique<std::vector<std::unique_ptr<QueryToken>>>();

    for (auto & unvalidatedToken : unvalidatedTokens)
    {
        auto token = std::make_unique<DeclarativeToken>(entityType, unvalidatedToken);
        declarativeTokens->push_back(std::move(token));
    }

    return declarativeTokens;
}
