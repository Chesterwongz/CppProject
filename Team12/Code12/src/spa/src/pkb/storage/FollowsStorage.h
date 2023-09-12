#pragma once

#include <vector>
#include <unordered_map>
#include <set>

class FollowsStorage {
public:
    // Constructor
    FollowsStorage();

    // Setter for follows relationship
    void setFollows(int statementNumber, int followingStatement);

    // Getter for all follows relationship
    std::set<int> getAllFollows(int statementNumber);

    // Getter for all followed by relationship
    std::set<int> getAllFollowedBy(int statementNumber);

    // Getter for immediate follows relationship
    int getImmediateFollows(int statementNumber);

    // Getter for immediate followed by relationship
    int getImmediateFollowedBy(int statementNumber);

private:
    // Data structure for follows relationship (statement number -> following statement numbers)
    std::unordered_map<int, std::set<int>> followsFrom;

    // Data structure for followed by relationship (following statement number -> statement numbers)
    std::unordered_map<int, std::set<int>> followsTo;
};
