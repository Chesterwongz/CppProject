#include "ProgramNode.h"

void ProgramNode::accept(Extractor *e) const {
    e->visitProgram(this);
}

vector<std::string> ProgramNode::getProcNames() const {
    vector<std::string> procNames;
    for (auto &child : getChildren()) {
        procNames.push_back(child->getValue());
    }
    return procNames;
}
