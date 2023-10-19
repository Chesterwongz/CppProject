#pragma once

#include <string>

class IModifiesWriter {
 public:
  virtual ~IModifiesWriter() = default;
  virtual void addModifies(const std::string& varName, int stmtNum) = 0;
  virtual void addModifies(const std::string& varName,
                           const std::string& procName) = 0;
};
