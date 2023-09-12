#pragma once

#include "ITokenHandler.h"

/**
 * The default chaining behavior can be implemented inside a base handler class.
 */
class BaseTokenizer : public ITokenHandler {
private:
    std::shared_ptr<ITokenHandler> nextHandler;
public:
    Token tokenize(char nextCh, std::shared_ptr<InputStream> inputStream) override;
    std::shared_ptr<ITokenHandler> setNext(std::shared_ptr<ITokenHandler> handler) override;
};
