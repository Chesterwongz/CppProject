#ifndef PKBWRITER_H
#define PKBWRITER_H

#include <string>
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"

class PKBWriter {
public:
    // Constructor
    PKBWriter();

    // Add follows relationship
    void setFollowsRelationship(int statementNumber, int followingStatement);

    // Add parent relationship
    void setParentRelationship(int statementNumber, int childStatement);

    // Add modifies relationship
    void setModifiesRelationship(const std::string& variableName, int statementNumber);

    // Add uses relationship
    void setUsesRelationship(const std::string& variableName, int statementNumber);

    // Add statement
    void setStatement(const std::string& statementType, int statementNumber);

private:
    FollowsStorage followsStorage;
    ModifiesStorage modifiesStorage;
    ParentStorage parentStorage;
    StatementStorage statementStorage;
    UsesStorage usesStorage;
};

#endif // PKBWRITER_H
