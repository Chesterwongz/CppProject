#include "ReadParser.h"

std::unique_ptr<TNode> ReadParser::makeTNode() const {
  return std::make_unique<ReadNode>(context.getLineNum());
}
