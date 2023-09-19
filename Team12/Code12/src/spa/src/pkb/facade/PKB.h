#pragma once

#include "PKBWriter.h"
#include "PKBReader.h"
#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"
#include "PKBStorage.h"

class PKB {
private:
    Storage storage;

public:
    PKBReader reader;
    PKBWriter writer;
    PKB() : storage(), writer(storage), reader(storage) {};
    PKBWriter& getWriter() { return writer; }
    PKBReader* getReader() { return &reader; }
};
