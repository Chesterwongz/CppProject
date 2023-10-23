#pragma once

#include <string>

class IUsesWriter {
 public:
  virtual ~IUsesWriter() = default;
  virtual void addUses(const std::string& varName, int stmtNum) = 0;
  virtual void addUses(const std::string& varName,
                       const std::string& procName) = 0;
};
