#include "InputStream.h"

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
    while (peekCursor < fileContents.length() && predicate(peekChar)) {
        str.push_back(peekChar);
        peekChar = fileContents.at(++peekCursor);
    }
    return str;
}

std::string InputStream::read() {
    return std::string(1, fileContents.at(cursor++));
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
