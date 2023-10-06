#pragma once

#include <string>

class IModifiesWriter {
 public:
  virtual ~IModifiesWriter() = default;
  virtual void setModifiesRelationship(const std::string& variableName,
                                       int statementNumber) = 0;
};
