#pragma once

#include <set>
#include <string>

class IDesignEntitiesReader {
 public:
  virtual std::set<std::string> getAllVariables() = 0;
  virtual std::set<std::string> getAllConstants() = 0;
  virtual std::set<std::string> getAllProcedures() = 0;
};
