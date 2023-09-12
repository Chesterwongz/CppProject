#include "TermParser.h"

std::unique_ptr<AbstractParser> TermParser::getNextParser() const {
    return std::make_unique<FactorParser>(context);
}

TokenType TermParser::getExpectedTokenType() const {
    return TokenType::TERM_OP;
}

TNodeType TermParser::getExpectedTNodeType() const {
    return TNodeType::TNODE_TERM;
}
