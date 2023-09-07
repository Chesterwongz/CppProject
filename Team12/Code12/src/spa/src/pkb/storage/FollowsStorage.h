#ifndef FOLLOWSSTORAGE_H
#define FOLLOWSSTORAGE_H

#include <vector>
#include <map>

class FollowsStorage {
public:
    // Constructor
    FollowsStorage();

    // Setter for follows relationship
    void setFollows(int statementNumber, int followingStatement);

    // Getter for all follows relationship
    std::vector<int> getAllFollows(int statementNumber);

    // Getter for all followed by relationship
    std::vector<int> getAllFollowedBy(int statementNumber);

    // Getter for immediate follows relationship
    int getImmediateFollows(int statementNumber);

    // Getter for immediate followed by relationship
    int getImmediateFollowedBy(int statementNumber);

private:
    // Data structure for follows relationship (statement number -> following statement numbers)
    std::map<int, std::vector<int>> followsFrom;

    // Data structure for followed by relationship (following statement number -> statement numbers)
    std::map<int, std::vector<int>> followsTo;
};

#endif // FOLLOWSSTORAGE_H
