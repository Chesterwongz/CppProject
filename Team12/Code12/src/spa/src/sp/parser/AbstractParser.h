#pragma once

#include <memory>
#include <utility>
#include "IParser.h"
#include "sp/tokenizer/TokenStream.h"

class AbstractParser : public IParser {
private:
    std::shared_ptr<TokenStream> tokenStream;
protected:
    explicit AbstractParser(std::shared_ptr<TokenStream> tokenStream) : tokenStream(std::move(tokenStream)) {}
public:
    std::unique_ptr<TNode> parse() override = 0;
};