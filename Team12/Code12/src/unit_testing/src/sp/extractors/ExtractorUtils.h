#pragma once

#include <vector>
#include <memory>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "catch.hpp"
#include "sp/extractors/DesignExtractor.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/StmtListNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/parser/toplevelparsers/ProgramParser.h"
#include "sp/parser/condexprparser/CondExprParser.h"
#include "../mocks/MockPKBWriter.h"
#include "../ast/TNodeUtils.h"
#include "AbstractionTypes.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::unordered_map, std::set;

unique_ptr<Extractor> getExtractor(MockPKBWriter &mockPKBWriter, AbstractionType abstractionType);

void extractAbstraction(TNode* node, MockPKBWriter &mockPKBWriter, AbstractionType abstractionType);

void extractAbstraction(const string& input, MockPKBWriter &mockPKBWriter, AbstractionType abstractionType);
