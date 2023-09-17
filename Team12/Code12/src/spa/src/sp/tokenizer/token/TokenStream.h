#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "sp/ast/TNode.h"
#include "common/utils/StringUtils.h"
#include "sp/tokenizer/handlers/ITokenHandler.h"
#include "sp/tokenizer/handlers/IntegerTokenizer.h"
#include "sp/tokenizer/token/InputStream.h"

class TokenStream {
private:
    int cursor;
    std::vector<Token> tokenLst;
    std::optional<Token> lookAhead;

    /**
     * Gets the next token from the inputStream and irreversibly moves the inputStream forward.
     */
    static std::optional<Token> nextToken(InputStream &inputStream, ITokenHandler &tokenizerChain);

public:
    static std::unique_ptr<TokenStream> initialize(std::string fileContents, ITokenHandler &tokenizerChain);

    /**
     * Gets the current token.
     * Returns std::nullopt if end of input has been reached.
     */
    std::optional<Token> peek();

    /**
     * Returns the current token and moves to the nextToken token.
     * Returns std::nullopt if end of input has been reached.
     */
    std::optional<Token> eat();
};
