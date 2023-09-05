#include "ProgramParser.h"

std::unique_ptr<TNode> ProgramParser::parse() {
    return std::make_unique<TNode>(TNodeType::TNODE_PROGRAM);
}
