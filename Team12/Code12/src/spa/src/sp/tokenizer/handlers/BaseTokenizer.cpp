#include "BaseTokenizer.h"

std::shared_ptr<ITokenHandler> BaseTokenizer::setNext(std::shared_ptr<ITokenHandler> handler) {
    this->nextHandler = handler;
    // Returning a handler from here will let us link handlers in a convenient
    // way like this:
    // handler1->setNext(handler1)->setNext(handler1);
    return nextHandler;
}

Token BaseTokenizer::tokenize(char nextCh, std::shared_ptr<InputStream> inputStream) {
    if (this->nextHandler) {
        return this->nextHandler->tokenize(nextCh, inputStream);
    }
    throw SyntaxError(std::string(1, nextCh));
}