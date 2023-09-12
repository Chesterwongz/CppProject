#pragma once

#include "PKBWriter.h"
#include "PKBReader.h"

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
    PKB() : storage(), writer(storage), reader(storage) {};
};
