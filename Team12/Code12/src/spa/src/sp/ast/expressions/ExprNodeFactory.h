#pragma once

#include <memory>
#include <string>
#include <utility>

#include "sp/ast/expressions/ExprNode.h"
#include "sp/ast/expressions/arithmetic/ArithmNode.h"
#include "sp/ast/expressions/arithmetic/DivNode.h"
#include "sp/ast/expressions/arithmetic/MinusNode.h"
#include "sp/ast/expressions/arithmetic/ModNode.h"
#include "sp/ast/expressions/arithmetic/PlusNode.h"
#include "sp/ast/expressions/arithmetic/TimesNode.h"
#include "sp/ast/expressions/conditional/AndNode.h"
#include "sp/ast/expressions/conditional/OrNode.h"
#include "sp/constants/OperatorConstants.h"
#include "sp/exceptions/UnexpectedTokenException.h"

class ExprNodeFactory : public ExprNode {
 public:
  static unique_ptr<TNode> makeNode(const std::string& kOp,
                                    std::unique_ptr<TNode> leftExpr,
                                    std::unique_ptr<TNode> rightExpr);
};
