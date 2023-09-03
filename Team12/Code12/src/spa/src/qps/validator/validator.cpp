#pragma once

#include "validator.h"
#include "qps/token/declarativeToken/declarativeToken.h"

bool Validator::validateTokens(Token *token) {
    if (token == nullptr) {
        return false;
    }

    bool isTokenLexicallyValid = validateTokenSyntax(token);
    bool isTokenContextValid = validateTokenContext(token);

    return isTokenLexicallyValid && isTokenContextValid;
}

bool Validator::validateTokenSyntax(Token *token) {
    Token *curr = token;
    while (curr != nullptr) {
        // traverse linked-list and validate all tokens
        if (!token->validate()) {
            return false;
        }
        curr = token->getNext();
    }
    return true;
}

bool Validator::validateTokenContext(Token *token) {
    std::map<std::string, Token*>  declarativeTokensMap = {};
    Token *curr = token;
    while (curr != nullptr) {
        if (auto *declarativeToken = dynamic_cast<DeclarativeToken *>(token)) {
            std::string tokenSynonym = declarativeToken->getSynonym();
            declarativeTokensMap[tokenSynonym] = declarativeToken;
        } else {
            // todo: logic to check if synonym used exists
        }
        curr = token->getNext();
    }
    return true;
}
