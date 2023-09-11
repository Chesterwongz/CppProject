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
    std::optional<Token> lookAhead;
    std::shared_ptr<InputStream> inputStream;
    std::unique_ptr<ITokenHandler> tokenizerChain;

    /**
     * Gets the next token from the inputStream and irreversibly moves the inputStream forward.
     */
    std::optional<Token> nextToken();
public:
    explicit TokenStream(std::string fileContent, std::unique_ptr<ITokenHandler> tokenizerChain);
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
