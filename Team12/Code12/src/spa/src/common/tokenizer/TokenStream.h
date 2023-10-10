#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "ITokenHandler.h"
#include "InputStream.h"
#include "common/utils/StringUtils.h"

template <typename T>
class TokenStream {
 private:
  int cursor;
  std::optional<T> currToken;
  std::vector<T> tokenLst;

  /**
   * Gets the next token from the inputStream and irreversibly moves the
   * inputStream forward.
   */
  static inline std::optional<T> nextToken(InputStream &inputStream,
                                           ITokenHandler<T> &tokenizerChain) {
    inputStream.readWhile(StringUtils::isWhiteSpace);  // Skip whitespaces

    if (inputStream.isEnd()) {
      return std::nullopt;
    }

    return tokenizerChain.tokenize(inputStream.peek(), inputStream);
  }

 public:
  static inline std::unique_ptr<TokenStream<T>> initialize(
      InputStream &inputStream, ITokenHandler<T> &tokenizerChain) {
    std::unique_ptr<TokenStream<T>> tokenStream =
        std::make_unique<TokenStream<T>>();
    // Prime the tokenizer with the first token
    std::optional<T> tokenOpt = nextToken(inputStream, tokenizerChain);
    tokenStream->currToken = tokenOpt;
    while (tokenOpt.has_value()) {
      tokenStream->tokenLst.push_back(tokenOpt.value());
      tokenOpt = nextToken(inputStream, tokenizerChain);
    }
    return tokenStream;
  }

  [[nodiscard]] inline int getCursor() const { return cursor; }

  inline void setCursor(int n) {
    cursor = n;
    currToken = tokenLst[cursor];
  }

  /**
   * Gets the current token.
   * Returns std::nullopt if end of input has been reached.
   */
  [[nodiscard]] inline std::optional<T> peek() const { return currToken; }

  /**
   * Returns the current token and moves to the nextToken token.
   * Returns std::nullopt if end of input has been reached.
   */
  inline std::optional<T> eat() {
    if (!currToken.has_value()) return currToken;

    std::optional<T> temp = currToken;
    currToken = cursor + 1 < tokenLst.size() ? std::optional{tokenLst[++cursor]}
                                             : std::nullopt;
    return temp;
  }

//  // For testing only:
//  TokenStream<T>(std::vector<T> tokenList)
//      : tokenLst(tokenList), cursor(0), currToken(tokenList[0]) {}
//
//  TokenStream<T>() {}
};
