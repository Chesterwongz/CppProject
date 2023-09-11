#pragma once

#include <memory>
#include <string>

#include "sp/extractors/DesignExtractor.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/StmtListNode.h"
#include "sp/ast/statements/ReadNode.h"
#include "sp/ast/statements/PrintNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/ast/statements/AssignNode.h"
#include "sp/ast/terminals/ConstNode.h"
#include "sp/ast/terminals/VarNode.h"
#include "sp/ast/expressions/arithmetic/PlusNode.h"
#include "sp/ast/expressions/relational/LtNode.h"
#include "sp/ast/expressions/relational/EqNode.h"

using std::unique_ptr, std::make_unique, std::string;

unique_ptr<ProgramNode> makeProgramNode();

unique_ptr<ProcNode> makeProcNode(const string& procName);

unique_ptr<ReadNode> makeReadNode(int lineNum, const string& varName);

unique_ptr<PrintNode> makePrintNode(int lineNum, const string& varName);

unique_ptr<AssignNode> makeAssignWithPlusNode(int lineNum, const string& leftVar, const string& rightVar, const string& constValue);

unique_ptr<LtNode> makeLtNode(const string& leftVar, const string& rightVar);

unique_ptr<EqNode> makeEqNode(const string& leftVar, const string& rightVar);
