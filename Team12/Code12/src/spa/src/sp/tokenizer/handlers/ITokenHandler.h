#pragma once

#include <string>
#include <memory>

#include "sp/tokenizer/token/InputStream.h"

#include "sp/exceptions/SyntaxError.h"
#include "sp/tokenizer/token/Token.h"

class ITokenHandler {
public:
    virtual ~ITokenHandler() = default;
    virtual Token tokenize(char nextCh, std::shared_ptr<InputStream> inputStream) = 0;
    virtual std::shared_ptr<ITokenHandler> setNext(std::shared_ptr<ITokenHandler> handler) = 0;
};
