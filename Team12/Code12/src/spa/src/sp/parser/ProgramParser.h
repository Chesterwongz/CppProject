#pragma once

#include "IParser.h"
#include <memory>
#include <utility>
#include "sp/tokenizer/TokenStream.h"
#include "sp/utils/FileReaderUtils.h"
#include "sp/tokenizer/handlers/NameTokenizer.h"
#include "sp/tokenizer/handlers/IntegerTokenizer.h"

class ProgramParser : public IParser {
private:
    std::shared_ptr<TokenStream> tokenStream;
public:
    explicit ProgramParser(std::string &filePath);
    std::unique_ptr<TNode> parse() override;
};
