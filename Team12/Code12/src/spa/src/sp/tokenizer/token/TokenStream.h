#pragma once

#include <functional>
#include <string>
#include "sp/tokenizer/token/TokenType.h"

class TokenStream {
private:
    int cursor;
    std::string fileContents;
public:
    explicit TokenStream(std::string &fileContents);

    bool hasMoreTokens();
    char peek();
    char read();
    std::string readWhile(const std::function<bool(const char)> &predicate);
};


