#include "TermParser.h"

std::unique_ptr<AbstractParser> TermParser::getNextParser() const {
    return std::make_unique<FactorParser>(context);
}

SpTokenType TermParser::getExpectedTokenType() const {
    return SpTokenType::TERM_OP;
}

TNodeType TermParser::getExpectedTNodeType() const {
    return TNodeType::TNODE_TERM;
}
