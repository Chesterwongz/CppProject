#include "ProcedureParser.h"

/* procedure: 'procedure' proc_name '{' stmtLst '}'
 * if tokenizer is not Keyword("procedure"): return NULL
 * proc_name = parseName()
 * if parseKeyword("{") is NULL: throw syntax error
 * node = new ProcNode(proc_name)
 * childNode = parseStmtLst()
 * node.addChild(childNode)
 * if context->tryEatExpected("}") is NULL: throw syntax error
 * return node
 */
std::optional<std::unique_ptr<TNode>> ProcedureParser::parse() {
    if (!context->tryEatExpected(SpTokenType::NAME, keyword::kProcedure).has_value())
        return std::nullopt;

    std::string procName = context->forceEatExpected(SpTokenType::NAME);

    std::optional<std::unique_ptr<TNode>> stmtLstNodeOpt = StmtLstParser(context).parse();
    requireTNodeOpt(TNodeType::TNODE_PROCEDURE)(stmtLstNodeOpt);

    std::unique_ptr<TNode> procNode = std::make_unique<ProcNode>(procName);
    procNode->addChild(std::move(stmtLstNodeOpt.value()));
    return procNode;
}
