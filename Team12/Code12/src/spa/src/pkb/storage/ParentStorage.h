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

    // Getter for all children relationship
    std::set<int> getAllChildren(int statementNumber);

    // Getter for all parents relationship
    std::set<int> getAllParents(int statementNumber);

    // Getter for immediate child relationship
    int getImmediateChild(int statementNumber);

    // Getter for immediate parent relationship
    int getImmediateParent(int statementNumber);

private:
    // Data structure for parent relationship (statement number -> child statement numbers)
    std::unordered_map<int, std::set<int>> parentOf;

    // Data structure for child relationship (child statement number -> parent statement numbers)
    std::unordered_map<int, std::set<int>>childOf;
};
