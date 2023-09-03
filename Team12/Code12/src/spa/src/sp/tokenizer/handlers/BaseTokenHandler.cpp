#include "BaseTokenHandler.h"

std::shared_ptr<ITokenHandler> BaseTokenHandler::setNext(std::shared_ptr<ITokenHandler> handler) {
    this->nextHandler = handler;
    // Returning a handler from here will let us link handlers in a convenient
    // way like this:
    // handler1->setNext(handler1)->setNext(handler1);
    return nextHandler;
}

Token BaseTokenHandler::handle(std::shared_ptr<TokenStream> tokenStream) {
    if (this->nextHandler) {
        return this->nextHandler->handle(tokenStream);
    }
    throw SyntaxError(tokenStream->peek());
}