#pragma once

#include <vector>
#include <unordered_map>
#include <set>

class ParentStorage {
public:
    // Constructor
    ParentStorage();

    // Setter for parent relationship
    void setParent(int statementNumber, int childStatement);

    void setParentStar(int statementNumber, int childStatement);

    std::set<int> getAllParents();

    std::set<int> getAllChildren();

    // Getter for all children relationship
    std::set<int> getAllChildren(int statementNumber);

    // Getter for all parents relationship
    std::set<int> getAllParents(int statementNumber);

    // Getter for immediate children relationship - 1 parent can have multiple children
    std::set<int> getImmediateChildren(int statementNumber);

    // Getter for immediate parent relationship - 1 child has at most 1 immediate parent
    int getImmediateParent(int statementNumber);

private:
    // Data structure for parent relationship (statement number -> immediate children statement numbers)
    std::unordered_map<int, std::set<int>> immediateChildrenOf;

    // Data structure for parent* relationship (statement number -> all children statement numbers)
    std::unordered_map<int, std::set<int>> childrenOf;

    // Data structure for child relationship (child statement number -> parents statement numbers)
    std::unordered_map<int, std::set<int>> parentsOf;
};
