#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "common/utils/StringUtils.h"
#include "sp/tokenizer/handlers/ITokenHandler.h"
#include "sp/tokenizer/handlers/ConstTokenHandler.h"
#include "sp/tokenizer/token/TokenStream.h"

class Tokenizer {
private:
    std::unique_ptr<ITokenHandler> handlerPipeline;
    std::shared_ptr<TokenStream> tokenStream;
public:
    explicit Tokenizer(std::string &fileContent);
    std::optional<Token> nextToken();
};
