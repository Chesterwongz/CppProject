#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

class FollowsStorage {
public:
    FollowsStorage();

    // Setter for follows* relationship
    void setFollows(int statementNumber, int followingStatement);

    // Return s2 that satisfies Follows(s1, s2) where s1 is statementNumber
    int getImmediateFollows(int statementNumber);

    // Return s1 that satisfies Follows(s1, s2) where s2 is statementNumber
    int getImmediateFollowedBy(int statementNumber);

    // Return all s2 that satisfies Follows*(s1, s2) where s1 is statementNumber
    std::set<int> getAllFollows(int statementNumber);

    // Return all s1 that satisfies Follows*(s1, s2) where s2 is statementNumber
    std::set<int> getAllFollowedBy(int statementNumber);

private:
    // (statement number -> following statement numbers)
    std::unordered_map<int, std::set<int>> followsFrom;

    // (following statement number -> statement numbers)
    std::unordered_map<int, std::set<int>> followsTo;
};
