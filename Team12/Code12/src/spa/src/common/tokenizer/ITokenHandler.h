#pragma once

#include <memory>

#include "common/tokenizer/InputStream.h"

#include "sp/exceptions/SyntaxError.h"

template <typename T>
class ITokenHandler {
public:
    virtual ~ITokenHandler() = default;

    virtual T tokenize(char nextCh, InputStream &inputStream) = 0;

    virtual ITokenHandler<T> &setNext(std::unique_ptr<ITokenHandler<T>> handler) = 0;
};
