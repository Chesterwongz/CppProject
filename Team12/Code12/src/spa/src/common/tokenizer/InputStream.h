#pragma once

#include <functional>
#include <string>
#include <utility>

#include "sp/tokenizer/token/SpTokenType.h"

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
  std::string read();
  std::string readWhile(const std::function<bool(const char)> &predicate);
};
