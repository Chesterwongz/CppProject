#pragma once

#include <string>
#include <memory>

#include "sp/tokenizer/token/TokenStream.h"

#include "sp/exceptions/SyntaxError.h"
#include "sp/tokenizer/token/Token.h"

class ITokenHandler {
public:
    virtual ~ITokenHandler() = default;
    virtual Token handle(std::shared_ptr<TokenStream>) = 0;
    virtual std::shared_ptr<ITokenHandler> setNext(std::shared_ptr<ITokenHandler> handler) = 0;
};
