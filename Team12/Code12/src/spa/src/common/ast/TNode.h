#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "TNodeType.h"
#include "sp/extractors/Extractor.h"

class Extractor;

using std::string, std::unique_ptr, std::vector;

class TNode {
 private:
  string value;
  TNodeType type;
  vector<unique_ptr<TNode>> children;

 public:
  explicit TNode(TNodeType type);
  TNode(TNodeType type, std::string value);

  virtual ~TNode() = default;

  void addChild(unique_ptr<TNode> child);

  [[nodiscard]] string getValue() const;

  [[nodiscard]] TNodeType getType() const;

  [[nodiscard]] TNode &getChildAt(int index) const;

  [[nodiscard]] string getChildValueAt(int index) const;

  [[nodiscard]] virtual vector<TNode *> getChildren() const;

  virtual void accept(Extractor &e) const;

  virtual void cleanup(Extractor &e) const;

  [[nodiscard]] virtual bool isEqual(const TNode &other) const;

  friend bool operator==(const TNode &lhs, const TNode &rhs);

  friend bool operator!=(const TNode &lhs, const TNode &rhs);
};
