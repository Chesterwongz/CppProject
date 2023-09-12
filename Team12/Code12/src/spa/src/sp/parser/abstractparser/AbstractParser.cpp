#include "AbstractParser.h"

std::function<std::unique_ptr<TNode>(std::optional<std::unique_ptr<TNode>>)>
AbstractParser::requireTNode(TNodeType nodeType) {
    int lineNum = context->getLineNum();
    return [nodeType, lineNum](std::optional<std::unique_ptr<TNode>> nodeOpt) {
        if (!nodeOpt.has_value()) throw SyntaxError(TNodeTypeUtils::toString(nodeType), lineNum);
        return std::move(nodeOpt.value());
    };
}
