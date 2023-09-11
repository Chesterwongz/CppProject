#pragma once

#include <string>
#include <memory>

#include "sp/tokenizer/token/InputStream.h"

#include "sp/exceptions/SyntaxError.h"
#include "sp/tokenizer/token/Token.h"

class ITokenizer {
public:
    virtual ~ITokenizer() = default;
    virtual Token tokenize(char nextCh, std::shared_ptr<InputStream>) = 0;
    virtual std::shared_ptr<ITokenizer> setNext(std::shared_ptr<ITokenizer> handler) = 0;
};
