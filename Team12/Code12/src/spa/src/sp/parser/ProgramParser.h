#pragma once

#include <memory>
#include <utility>
#include "sp/tokenizer/TokenStream.h"
#include "IParser.h"
#include "AbstractParser.h"

class ProgramParser : public AbstractParser {
public:
    explicit ProgramParser(std::shared_ptr<TokenStream> tokenStream)
            : AbstractParser(std::move(tokenStream)) {};
    std::unique_ptr<TNode> parse() override;
};
