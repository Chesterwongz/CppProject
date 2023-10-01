#pragma once

#include <memory>
#include "sp/tokenizer/handlers/SpDelimiterTokenizer.h"
#include "sp/tokenizer/handlers/SpExprOpTokenizer.h"
#include "sp/tokenizer/handlers/SpIntegerTokenizer.h"
#include "sp/tokenizer/handlers/SpNameTokenizer.h"
#include "sp/tokenizer/handlers/SpTermOpTokenizer.h"
#include "sp/tokenizer/handlers/SpRelOpTokenizer.h"
#include "sp/tokenizer/handlers/SpCondOpTokenizer.h"
#include "common/tokenizer/TokenStream.h"
#include "sp/utils/FileReaderUtils.h"

class SpTokenizer {
public:
    static std::unique_ptr<TokenStream<SpToken>> tokenize(string filePath);
};


