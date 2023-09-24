#pragma once

#include <memory>
#include "sp/tokenizer/handlers/DelimiterTokenizer.h"
#include "sp/tokenizer/handlers/ExprOpTokenizer.h"
#include "sp/tokenizer/handlers/ITokenHandler.h"
#include "sp/tokenizer/handlers/IntegerTokenizer.h"
#include "sp/tokenizer/handlers/NameTokenizer.h"
#include "sp/tokenizer/handlers/TermOpTokenizer.h"
#include "sp/tokenizer/token/TokenStream.h"
#include "sp/utils/FileReaderUtils.h"

class Tokenizer {
public:
    static unique_ptr<TokenStream> tokenize(string filePath);
};


