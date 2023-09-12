#pragma once

#include "pkb/facade/PKBReader.h"
#include "pkb/facade/PKBWriter.h"

struct Storage {
    DesignEntitiesStorage designEntitiesStorage;
    FollowsStorage followsStorage;
    ModifiesStorage modifiesStorage;
    ParentStorage parentStorage;
    StatementStorage statementStorage;
    UsesStorage usesStorage;
};

class PKB {
private:
    PKBReader reader;
    PKBWriter writer;
    Storage storage;

public:
    PKB() {
        storage = {DesignEntitiesStorage(), FollowsStorage(), ModifiesStorage(), ParentStorage(), StatementStorage(), UsesStorage()};
        writer = PKBWriter(storage);
    }
};
