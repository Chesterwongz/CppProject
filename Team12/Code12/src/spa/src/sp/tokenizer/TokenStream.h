#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "common/utils/StringUtils.h"
#include "sp/tokenizer/handlers/ITokenizer.h"
#include "sp/tokenizer/handlers/IntegerTokenizer.h"
#include "sp/tokenizer/token/InputStream.h"

class Tokenizer {
private:
    std::optional<Token> lookAhead;
    std::shared_ptr<InputStream> inputStream;
    std::unique_ptr<ITokenizer> handlerPipeline;

    /**
     * Gets the next token from the inputStream and irreversibly moves the inputStream forward.
     */
    std::optional<Token> nextToken();
public:
    explicit Tokenizer(std::string &fileContent);
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
