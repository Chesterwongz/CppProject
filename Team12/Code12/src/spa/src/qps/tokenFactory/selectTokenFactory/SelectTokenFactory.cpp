#include <iostream>

#include "SelectTokenFactory.h"
#include "qps/token/selectToken/SelectToken.h"

bool SelectTokenFactory::isValid(UnvalidatedTokens unvalidatedTokens) {
    // should be [syn]
    if (unvalidatedTokens.size() != 1) return false;

    return isSynonym(unvalidatedTokens[0]);
}

TokenStreamPtr SelectTokenFactory::createTokens(UnvalidatedTokens unvalidatedTokens) {
    if (!isValid(unvalidatedTokens)) {
        throw std::runtime_error("Select token stream is invalid");
    }

    if (unvalidatedTokens.empty()) {
        return std::make_unique<std::vector<std::unique_ptr<QueryToken>>>();
    }

    TokenStreamPtr selectTokens = std::make_unique<std::vector<std::unique_ptr<QueryToken>>>();

    for (size_t i = 0; i < unvalidatedTokens.size(); i++)
    {
        std::cout << "Creating token for: " << unvalidatedTokens[i] << std::endl;
        auto token = std::make_unique<SelectToken>(unvalidatedTokens[i]);
        selectTokens->push_back(std::move(token));
    }

    return selectTokens;
}
