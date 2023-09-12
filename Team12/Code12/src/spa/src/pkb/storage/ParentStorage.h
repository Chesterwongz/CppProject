#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

class ParentStorage {
public:
    // Constructor
    ParentStorage();

    // Setter for parent relationship
    void setParent(int statementNumber, int childStatement);

    // Getter for all children relationship
    std::unordered_set<int> getAllChildren(int statementNumber);

    // Getter for all parents relationship
    std::set<int> getAllParents(int statementNumber);

    // Getter for immediate children relationship - 1 parent can have multiple children
    std::unordered_set<int> getImmediateChildren(int statementNumber);

    // Getter for immediate parent relationship - 1 child has at most 1 immediate parent
    int getImmediateParent(int statementNumber);

private:
    // Data structure for parent relationship (statement number -> child statement numbers)
    std::unordered_map<int, std::unordered_set<int>> parentOf;

    // Data structure for child relationship (child statement number -> parent statement numbers)
    std::unordered_map<int, std::set<int>>childOf;
};
