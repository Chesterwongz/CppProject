#pragma once

#include <string>
#include <utility>

#include "common/ast/TNode.h"

class StmtNode : public TNode {
 private:
  int lineNum;

 public:
  explicit StmtNode(TNodeType type, std::string value, int lineNum)
      : TNode(type, std::move(value)), lineNum(lineNum) {}
  ~StmtNode() override = default;
  [[nodiscard]] int getLineNum() const;
  [[nodiscard]] bool isEqual(const TNode& other) const override;
};
