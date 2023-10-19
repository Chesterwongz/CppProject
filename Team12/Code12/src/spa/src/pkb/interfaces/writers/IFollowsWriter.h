#pragma once

class IFollowsWriter {
 public:
  virtual ~IFollowsWriter() = default;
  virtual void addFollows(int from, int to) = 0;
};
