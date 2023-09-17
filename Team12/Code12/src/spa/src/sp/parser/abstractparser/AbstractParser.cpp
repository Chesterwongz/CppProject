#include "AbstractParser.h"

std::function<void(const std::optional<std::unique_ptr<TNode>> &)>
AbstractParser::requireTNodeOpt(TNodeType nodeType) {
    int lineNum = context->getLineNum();
    return [nodeType, lineNum](const std::optional<std::unique_ptr<TNode>> &nodeOpt) {
        if (!nodeOpt.has_value()) throw SyntaxError(TNodeTypeUtils::toString(nodeType), lineNum);
    };
}
