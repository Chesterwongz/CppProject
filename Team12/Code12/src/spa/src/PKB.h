#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "pkb/storage/DesignEntitiesStorage.h"
#include "pkb/storage/FollowsStorage.h"
#include "pkb/storage/ModifiesStorage.h"
#include "pkb/storage/ParentStorage.h"
#include "pkb/storage/StatementStorage.h"
#include "pkb/storage/UsesStorage.h"
#include "pkb/facade/PKBReader.h"
#include "pkb/facade/PKBWriter.h"

using namespace std;
typedef short PROC;

class TNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is pointer

class PKB {
public:
	static VarTable* varTable; 
	static int setProcToAST(PROC p, TNode* r);
	static TNode* getRootAST (PROC p);

};