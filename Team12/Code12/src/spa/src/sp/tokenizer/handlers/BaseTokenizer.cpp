#include "BaseTokenizer.h"

ITokenHandler &BaseTokenizer::setNext(std::unique_ptr<ITokenHandler> handler) {
    this->nextHandler = std::move(handler);
    // Returning a handler from here will let us link handlers in a convenient
    // way like this:
    // handler1->setNext(handler1)->setNext(handler1);
    return *nextHandler;
}

Token BaseTokenizer::tokenize(char nextCh, InputStream &inputStream) {
    if (this->nextHandler) {
        return this->nextHandler->tokenize(nextCh, inputStream);
    }
    throw SyntaxError(std::string(1, nextCh));
}