#pragma once

#include "ITokenHandler.h"

/**
 * The default chaining behavior can be implemented inside a base handler class.
 */
class BaseTokenHandler : public ITokenHandler {
private:
    std::shared_ptr<ITokenHandler> nextHandler;
public:
    Token handle(std::shared_ptr<TokenStream> tokenStream) override;
    std::shared_ptr<ITokenHandler> setNext(std::shared_ptr<ITokenHandler> handler) override;
};
