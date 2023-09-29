#include "ExprParser.h"

std::unique_ptr<AbstractParser> ExprParser::getNextParser() const {
    return std::make_unique<TermParser>(context);
}

SpTokenType ExprParser::getExpectedTokenType() const {
    return SpTokenType::EXPR_OP;
}

TNodeType ExprParser::getExpectedTNodeType() const {
    return TNodeType::TNODE_EXPR;
}
