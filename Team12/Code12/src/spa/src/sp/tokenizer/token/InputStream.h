#pragma once

#include <functional>
#include <string>
#include "sp/tokenizer/token/TokenType.h"

class InputStream {
private:
    int cursor;
    std::string fileContents;
public:
    explicit InputStream(std::string &fileContents);

    bool isEnd();
    char peek();
    char read();
    std::string readWhile(const std::function<bool(const char)> &predicate);
};


