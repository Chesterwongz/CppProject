#pragma once

#include "ITokenHandler.h"

/**
 * The default chaining behavior can be implemented inside a base handler class.
 */
class BaseTokenizer : public ITokenHandler {
private:
    std::unique_ptr<ITokenHandler> nextHandler;
public:
    Token tokenize(char nextCh, InputStream &inputStream) override;

    ITokenHandler &setNext(std::unique_ptr<ITokenHandler> handler) override;
};
