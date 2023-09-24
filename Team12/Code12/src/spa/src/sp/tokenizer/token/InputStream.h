#pragma once

#include <functional>
#include <string>
#include "TokenType.h"

class InputStream {
private:
    int cursor;
    std::string fileContents;
public:
    explicit InputStream(std::string fileContents);

    bool isEnd();
    char peek();
    std::string peekWhile(const std::function<bool(const char)> &predicate);
    std::string readN(int n);
    char read();
    std::string readWhile(const std::function<bool(const char)> &predicate);

};


