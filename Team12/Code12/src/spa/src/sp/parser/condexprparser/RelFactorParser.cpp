#include "RelFactorParser.h"

//    rel_factor: var_name | const_value | expr
std::optional<std::unique_ptr<TNode>> RelFactorParser::parse() {
  std::optional<std::unique_ptr<TNode>> nodeOpt = ExprParser(context).parse();
  return nodeOpt;
}
