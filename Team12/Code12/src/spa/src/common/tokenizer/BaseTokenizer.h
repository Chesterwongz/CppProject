#pragma once

#include <memory>
#include <string>
#include <utility>

#include "ITokenHandler.h"
#include "common/exceptions/CommonSyntaxError.h"

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
    throw CommonSyntaxError(std::string(1, nextCh));
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
