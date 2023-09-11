#pragma once

#include "validator.h"
#include "qps/token/declarativeToken/declarativeToken.h"

bool Validator::validateTokens(std::vector<QueryToken> *queryTokenVector) {
    for (QueryToken &queryToken : *queryTokenVector) {
        if (!queryToken.semanticValidation()) {
            return false;
        }
    }
    return true;
};
