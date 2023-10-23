#pragma once

#include <string>

#include "SpTokenType.h"

using std::string;

class SpToken {
 private:
  SpTokenType type;
  string value;

 public:
  explicit SpToken(SpTokenType type);
  SpToken(SpTokenType type, string value);
  [[nodiscard]] SpTokenType getType() const;
  [[nodiscard]] string getValue() const;
};
