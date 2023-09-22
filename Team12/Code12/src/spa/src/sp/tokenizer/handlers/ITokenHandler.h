#pragma once

#include <string>
#include <memory>

#include "sp/tokenizer/token/InputStream.h"

#include "sp/exceptions/SyntaxError.h"
#include "sp/tokenizer/token/Token.h"

class ITokenHandler {
public:
    virtual ~ITokenHandler() = default;

    virtual Token tokenize(char nextCh, InputStream &inputStream) = 0;

    virtual ITokenHandler &setNext(std::unique_ptr<ITokenHandler> handler) = 0;
};
