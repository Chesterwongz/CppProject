#include "PrintParser.h"

std::unique_ptr<TNode> PrintParser::makeTNode() const {
  return std::make_unique<PrintNode>(context->getLineNum());
}
