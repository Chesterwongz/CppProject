#pragma once

#include <memory>
#include <stack>
#include <string>
#include <unordered_set>

#include "common/tokenizer/TokenStream.h"
#include "sp/exceptions/DuplicateProcNameException.h"
#include "sp/exceptions/UnexpectedTokenException.h"
#include "sp/tokenizer/SpTokenizer.h"

class ParserContext {
 private:
  int lineNum{0};
  std::stack<int> savePositionStack;
  std::unique_ptr<TokenStream<SpToken>> tokenStream;

 public:
  explicit ParserContext(const std::string &input);

  [[nodiscard]] int getLineNum() const;

  void incrementLineNum();

  bool isExpected(SpTokenType expectedType);

  bool isExpected(SpTokenType expectedType, const string &expectedValue);

  /**
   * If current token in the tokenStream is the expected type, consumes the
   * token and returns its value. Does nothing and returns an empty optional
   * otherwise.
   */
  std::optional<std::string> tryEatExpected(SpTokenType expectedType);

  /**
   * If current token in the tokenStream is the expected type and has the
   * expectedValue, consumes the token and returns its value. Does nothing and
   * returns an empty optional otherwise.
   */
  std::optional<std::string> tryEatExpected(SpTokenType expectedType,
                                            const string &expectedValue);

  std::string forceEatExpected(SpTokenType expectedType,
                               const string &expectedValue);

  std::string forceEatExpected(SpTokenType expectedType);

  void saveContext();
  void removePrevSavedContext();
  void loadPrevSavedContext();
};
