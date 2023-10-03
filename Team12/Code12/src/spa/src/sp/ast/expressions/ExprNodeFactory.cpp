#include "ExprNodeFactory.h"

#include "sp/ast/expressions/relational/EqNode.h"
#include "sp/ast/expressions/relational/GtNode.h"
#include "sp/ast/expressions/relational/GteNode.h"
#include "sp/ast/expressions/relational/LtNode.h"
#include "sp/ast/expressions/relational/LteNode.h"
#include "sp/ast/expressions/relational/NeqNode.h"
#include "sp/exceptions/SyntaxError.h"

std::unique_ptr<TNode> ExprNodeFactory::makeNode(
    const std::string &kOp, std::unique_ptr<TNode> leftExpr,
    std::unique_ptr<TNode> rightExpr) {
  // Arithmetic op
  if (kOp == op::kPlus)
    return std::make_unique<PlusNode>(std::move(leftExpr),
                                      std::move(rightExpr));
  if (kOp == op::kMinus)
    return std::make_unique<MinusNode>(std::move(leftExpr),
                                       std::move(rightExpr));
  if (kOp == op::kTimes)
    return std::make_unique<TimesNode>(std::move(leftExpr),
                                       std::move(rightExpr));
  if (kOp == op::kDiv)
    return std::make_unique<DivNode>(std::move(leftExpr), std::move(rightExpr));
  if (kOp == op::kMod)
    return std::make_unique<ModNode>(std::move(leftExpr), std::move(rightExpr));

  // Conditional op
  if (kOp == op::kAnd)
    return std::make_unique<AndNode>(std::move(leftExpr), std::move(rightExpr));
  if (kOp == op::kOr)
    return std::make_unique<OrNode>(std::move(leftExpr), std::move(rightExpr));

  // Relational op
  if (kOp == op::kEq)
    return std::make_unique<EqNode>(std::move(leftExpr), std::move(rightExpr));
  if (kOp == op::kNeq)
    return std::make_unique<NeqNode>(std::move(leftExpr), std::move(rightExpr));
  if (kOp == op::kGt)
    return std::make_unique<GtNode>(std::move(leftExpr), std::move(rightExpr));
  if (kOp == op::kGte)
    return std::make_unique<GteNode>(std::move(leftExpr), std::move(rightExpr));
  if (kOp == op::kLt)
    return std::make_unique<LtNode>(std::move(leftExpr), std::move(rightExpr));
  if (kOp == op::kLte)
    return std::make_unique<LteNode>(std::move(leftExpr), std::move(rightExpr));

  throw SyntaxError(kOp);
}
