#pragma once

#include <string>
#include <vector>
#include "TNodeType.h"
#include "sp/extractors/Extractor.h"

class Extractor;

class TNode {
private:
    std::string value;
    TNodeType type;
    std::vector<std::unique_ptr<TNode>> children;

public:
    explicit TNode(TNodeType type);

    TNode(TNodeType type, std::string value);

    virtual ~TNode() = default;

    void addChild(std::unique_ptr<TNode> child);

    [[nodiscard]] std::string getValue() const;

    TNodeType getType();

    [[nodiscard]] virtual std::vector<TNode *> getChildren() const;

    virtual void accept(Extractor *e) const;

    virtual void cleanup(Extractor *e) const;

    [[nodiscard]] virtual bool isEqual(const TNode &other) const;

    friend bool operator==(const TNode &lhs, const TNode &rhs);

    friend bool operator!=(const TNode &lhs, const TNode &rhs);
};


