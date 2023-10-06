#pragma once

#include <string>

class IFollowsWriter {
 public:
  virtual ~IFollowsWriter() = default;
  virtual void setFollowsRelationship(int statementNumber,
                                      int followingStatement) = 0;
};
