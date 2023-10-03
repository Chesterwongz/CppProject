#pragma once

#include <string>

#include "ITokenHandler.h"
#include "sp/exceptions/SyntaxError.h"

/**
 * The default chaining behavior can be implemented inside a base handler class.
 */
template <typename T>
class BaseTokenizer : public ITokenHandler<T> {
 private:
  std::unique_ptr<ITokenHandler<T>> nextHandler;

 public:
  inline T tokenize(char nextCh, InputStream &inputStream) override {
    if (this->nextHandler) {
      return this->nextHandler->tokenize(nextCh, inputStream);
    }
    throw SyntaxError(std::string(1, nextCh));
  };

  inline ITokenHandler<T> &setNext(
      std::unique_ptr<ITokenHandler<T>> handler) override {
    this->nextHandler = std::move(handler);
    // Returning a handler from here will let us link handlers in a convenient
    // way like this:
    // handler1->setNext(handler1)->setNext(handler1);
    return *nextHandler;
  };
};
