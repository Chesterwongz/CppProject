#include "InputStream.h"

InputStream::InputStream(std::string &fileContents) : fileContents(fileContents), cursor(0) {}

bool InputStream::isEnd() {
    return this->cursor >= this->fileContents.length();
}

std::string InputStream::readWhile(const std::function<bool(const char)> &predicate) {
    std::string str;
    while (!isEnd() && predicate(peek())) {
        str += read();
    }
    return str;
}

char InputStream::peek() {
    return fileContents.at(cursor);
}

char InputStream::read() {
    char ch = peek();
    cursor++;
    return ch;
}