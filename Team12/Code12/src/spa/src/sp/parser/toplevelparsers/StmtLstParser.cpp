#include "StmtLstParser.h"

/* stmtLst: stmt+
 * node = new StmtNode()
 * childNode = parseStmt()
 * while childNode not NULL do:
 *      node.addChild(childNode)
 *      childNode = parseStmt()
 *  return node
 */
std::optional<std::unique_ptr<TNode>> StmtLstParser::parse() {
    context->forceEatExpected(TokenType::DELIM, delim::kOpenCurlyString);

    std::unique_ptr<TNode> stmtLstNode = std::make_unique<StmtListNode>();

    StmtParser stmtParser = StmtParser(context);
    std::optional<std::unique_ptr<TNode>> childNodeOpt = requireTNode(TNodeType::TNODE_STMT_LIST)(stmtParser.parse());
    while (childNodeOpt.has_value()) {
        stmtLstNode->addChild(std::move(childNodeOpt.value()));
        childNodeOpt = stmtParser.parse();
    }

    context->forceEatExpected(TokenType::DELIM, delim::kCloseCurlyString);

    return stmtLstNode;
}
