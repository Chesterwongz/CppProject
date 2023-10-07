#pragma once

#include <string>

class IDesignEntitiesWriter {
 public:
  virtual ~IDesignEntitiesWriter() = default;
  virtual void setVariable(const std::string& variableName) = 0;
  virtual void setConstant(const std::string& constantValue) = 0;
  virtual void setProcedure(const std::string& procedureName,
                            int startStatement) = 0;
};
