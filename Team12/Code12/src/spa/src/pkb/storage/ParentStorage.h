#ifndef PARENTSTORAGE_H
#define PARENTSTORAGE_H

#include <vector>
#include <map>

class ParentStorage {
public:
    // Constructor
    ParentStorage();

    // Setter for parent relationship
    void setParent(int statementNumber, int childStatement);

    // Getter for all children relationship
    std::vector<int> getAllChildren(int statementNumber);

    // Getter for all parents relationship
    std::vector<int> getAllParents(int statementNumber);

    // Getter for immediate child relationship
    int getImmediateChild(int statementNumber);

    // Getter for immediate parent relationship
    int getImmediateParent(int statementNumber);

private:
    // Data structure for parent relationship (statement number -> child statement numbers)
    std::map<int, std::vector<int>> parentOf;

    // Data structure for child relationship (child statement number -> parent statement numbers)
    std::map<int, std::vector<int>> childOf;
};

#endif // PARENTSTORAGE_H
