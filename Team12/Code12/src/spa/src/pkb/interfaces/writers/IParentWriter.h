#pragma once

#include <string>

class IParentWriter {
 public:
  virtual ~IParentWriter() = default;
  virtual void addParent(int parent, int child) = 0;
  virtual void setParentStarRelationship(int parent, int child) = 0;
};
