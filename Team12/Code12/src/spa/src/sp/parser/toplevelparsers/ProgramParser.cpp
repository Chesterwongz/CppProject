#include "ProgramParser.h"
#include "ProcedureParser.h"
#include "sp/ast/ProgramNode.h"

/* program: procedure+
 * node = new ProgramNode()
 * childNode = parseProcedure()
 * while childNode not NULL do:
 *      node.addChild(childNode)
 *      childNode = parseProcedure()
 * return node
*/
std::optional<std::unique_ptr<TNode>> ProgramParser::parse() {
    std::unique_ptr<TNode> root = std::make_unique<ProgramNode>();
    ProcedureParser procedureParser = ProcedureParser(this->context);
    std::optional<std::unique_ptr<TNode>> childNodeOpt = requireTNode(TNodeType::TNODE_PROGRAM)(
            procedureParser.parse());
    while (childNodeOpt.has_value()) {
        root->addChild(std::move(childNodeOpt.value()));
        childNodeOpt = procedureParser.parse();
    }
    return root;
}
