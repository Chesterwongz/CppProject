#include "TokenStream.h"

TokenStream::TokenStream(std::string &fileContents) : fileContents(fileContents), cursor(0) {}

bool TokenStream::hasMoreTokens() {
    return this->cursor < this->fileContents.length();
}

std::string TokenStream::readWhile(const std::function<bool(const char)> &predicate) {
    std::string str;
    while (hasMoreTokens() && predicate(peek())) {
        str += read();
    }
    return str;
}

char TokenStream::peek() {
    return fileContents.at(cursor);
}

char TokenStream::read() {
    char ch = peek();
    cursor++;
    return ch;
}