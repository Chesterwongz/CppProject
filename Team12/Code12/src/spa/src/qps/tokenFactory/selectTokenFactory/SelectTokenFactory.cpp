#include "SelectTokenFactory.h"
#include "qps/token/selectToken/SelectToken.h"

const bool SelectTokenFactory::isValid(UnvalidatedTokens unvalidatedTokens) {
    // should be ["Select", syn]
    if (unvalidatedTokens.size() != 2) return false;

    return unvalidatedTokens[0] == "Select" && isSynonym(unvalidatedTokens[1]);
}

TokenStreamPtr SelectTokenFactory::createTokens(ValidatedTokens validatedTokens) {
    if (validatedTokens.empty()) {
        return std::make_unique<std::vector<std::unique_ptr<QueryToken>>>();
    }

    TokenStreamPtr selectTokens = std::make_unique<std::vector<std::unique_ptr<QueryToken>>>();

    for (size_t i = 1; i < validatedTokens.size(); i++)
    {
        auto token = std::make_unique<SelectToken>(validatedTokens[i]);
        selectTokens->push_back(std::move(token));
    }

    return selectTokens;
}