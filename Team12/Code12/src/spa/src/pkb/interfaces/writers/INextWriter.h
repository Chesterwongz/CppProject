#pragma once

#include <string>

class INextWriter {
 public:
  virtual ~INextWriter() = default;
  virtual void addNext(int from, int to) = 0;
};
