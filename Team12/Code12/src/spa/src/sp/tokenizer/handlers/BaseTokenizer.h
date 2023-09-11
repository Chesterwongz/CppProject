#pragma once

#include "ITokenizer.h"

/**
 * The default chaining behavior can be implemented inside a base handler class.
 */
class BaseTokenizer : public ITokenizer {
private:
    std::shared_ptr<ITokenizer> nextHandler;
public:
    Token tokenize(char nextCh, std::shared_ptr<InputStream> tokenStream) override;
    std::shared_ptr<ITokenizer> setNext(std::shared_ptr<ITokenizer> handler) override;
};
