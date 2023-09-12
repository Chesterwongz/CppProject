#include "InputStream.h"

#include <utility>

InputStream::InputStream(std::string fileContents) : fileContents(std::move(fileContents)), cursor(0) {}

bool InputStream::isEnd() {
    return this->cursor >= this->fileContents.length();
}

char InputStream::peek() {
    return fileContents.at(cursor);
}

std::string InputStream::peekWhile(const std::function<bool(const char)> &predicate) {
    int peekCursor = cursor;
    std::string str;
    char peekChar = fileContents.at(peekCursor);
    while (!isEnd() && predicate(peekChar)) {
        str.push_back(peekChar);
        peekChar = fileContents.at(++peekCursor);
    }
    return str;
}

char InputStream::read() {
    char ch = peek();
    cursor++;
    return ch;
}

std::string InputStream::readN(int n) {
    std::string str = fileContents.substr(cursor, n);
    cursor += n;
    return str;
}

std::string InputStream::readWhile(const std::function<bool(const char)> &predicate) {
    std::string str;
    while (!isEnd() && predicate(peek())) {
        str += read();
    }
    return str;
}
