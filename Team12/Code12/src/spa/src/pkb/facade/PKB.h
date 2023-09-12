#pragma once

#include "PKBWriter.h"
#include "PKBReader.h"
#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"

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
