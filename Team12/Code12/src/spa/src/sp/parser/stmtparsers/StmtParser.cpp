#include "StmtParser.h"

/* stmt: read | print | call | while | if | assign
 * node = parseRead()
 * if node not NULL: return node
 * node = parsePrint()
 * if node not NULL: return node
 * node = parseCall()
 * if node not NULL: return node
 * node = parseWhile()
 * if node not NULL: return node
 * node = parseIf():
 * if node not NULL: return node
 * node parseAssign():
 * if node not NULL: return node
 * else: return NULL
 */
std::optional<std::unique_ptr<TNode>> StmtParser::parse() {
    if (context->isExpected(SpTokenType::DELIM, delim::kCloseCurlyString))
        return std::nullopt; // End of stmt block

    std::string keyword = context->forceEatExpected(SpTokenType::NAME);
    context->incrementLineNum();

    std::unique_ptr<AbstractParser> parser = StmtParserFactory::makeParser(keyword, context);
    std::optional<std::unique_ptr<TNode>> nodeOpt = parser->parse();
    if (nodeOpt.has_value()) return nodeOpt;

    // Goes here if assign stmt has keyword as var_name, e.g., `read = 1;`.
    // All stmts must be valid, so we can stop executing if something goes wrong here.
    nodeOpt = AssignParser(context, keyword).parse();
    requireTNodeOpt(TNodeType::TNODE_STMT)(nodeOpt);

    return nodeOpt;
}
