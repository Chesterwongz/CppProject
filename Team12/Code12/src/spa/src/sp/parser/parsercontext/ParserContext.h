#pragma once

#include <memory>
#include <unordered_set>
#include <stack>
#include <string>
#include "sp/exceptions/DuplicateProcNameException.h"
#include "sp/exceptions/UnexpectedTokenException.h"
#include "sp/tokenizer/token/TokenStream.h"
#include "sp/tokenizer/Tokenizer.h"

class ParserContext {
private:
    int lineNum{0};
    std::stack<int> savePositionStack;
    std::unique_ptr<TokenStream> tokenStream;

public:
    explicit ParserContext(const std::string &input);

    [[nodiscard]] int getLineNum() const;

    void incrementLineNum();

    bool isExpected(TokenType expectedType);

    bool isExpected(TokenType expectedType, const string &expectedValue);

    /**
     * If current token in the tokenStream is the expected type, consumes the token and returns its value.
     * Does nothing and returns an empty optional otherwise.
     */
    std::optional<std::string> tryEatExpected(TokenType expectedType);

    /**
     * If current token in the tokenStream is the expected type and has the expectedValue,
     * consumes the token and returns its value.
     * Does nothing and returns an empty optional otherwise.
     */
    std::optional<std::string> tryEatExpected(TokenType expectedType, const string &expectedValue);

    std::string forceEatExpected(TokenType expectedType, const string &expectedValue);

    std::string forceEatExpected(TokenType expectedType);

    void saveContext();

    void loadPrevSavedContext();
};
