#include "sp/ast/TNode.h"

#include <memory>
#include <catch.hpp>

#include "sp/ast/ProcNode.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/StmtListNode.h"
#include "sp/ast/expressions/arithmetic/DivNode.h"
#include "sp/ast/expressions/arithmetic/MinusNode.h"
#include "sp/ast/expressions/arithmetic/ModNode.h"
#include "sp/ast/expressions/arithmetic/PlusNode.h"
#include "sp/ast/expressions/arithmetic/TimesNode.h"
#include "sp/ast/expressions/conditional/AndNode.h"
#include "sp/ast/expressions/conditional/NotNode.h"
#include "sp/ast/expressions/conditional/OrNode.h"
#include "sp/ast/expressions/relational/EqNode.h"
#include "sp/ast/expressions/relational/GtNode.h"
#include "sp/ast/expressions/relational/GteNode.h"
#include "sp/ast/expressions/relational/LtNode.h"
#include "sp/ast/expressions/relational/LteNode.h"
#include "sp/ast/expressions/relational/NeqNode.h"
#include "sp/ast/statements/AssignNode.h"
#include "sp/ast/statements/CallNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/PrintNode.h"
#include "sp/ast/statements/ReadNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/ast/terminals/ConstNode.h"
#include "sp/ast/terminals/VarNode.h"

TEST_CASE("Test TNode equality - VarNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<VarNode>("x");
  std::unique_ptr<TNode> node2 = std::make_unique<VarNode>("x");
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - ConstNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<VarNode>("1");
  std::unique_ptr<TNode> node2 = std::make_unique<VarNode>("1");
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - ProcNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<ProcNode>("dummy");
  std::unique_ptr<TNode> node2 = std::make_unique<ProcNode>("dummy");
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - ProgramNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<ProgramNode>();
  std::unique_ptr<TNode> node2 = std::make_unique<ProgramNode>();
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - StmtListNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<StmtListNode>();
  node1->addChild(std::make_unique<AssignNode>(1));
  node1->addChild(std::make_unique<PrintNode>(2));
  std::unique_ptr<TNode> node2 = std::make_unique<StmtListNode>();
  node2->addChild(std::make_unique<AssignNode>(1));
  node2->addChild(std::make_unique<PrintNode>(2));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - AssignNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<AssignNode>(1);
  std::unique_ptr<TNode> node2 = std::make_unique<AssignNode>(1);
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - CallNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<CallNode>("p1", 1);
  std::unique_ptr<TNode> node2 = std::make_unique<CallNode>("p1", 1);
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - IfNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<IfNode>(1);
  std::unique_ptr<TNode> node2 = std::make_unique<IfNode>(1);
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - PrintNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<PrintNode>(1);
  std::unique_ptr<TNode> node2 = std::make_unique<PrintNode>(1);
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - ReadNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<ReadNode>(1);
  std::unique_ptr<TNode> node2 = std::make_unique<ReadNode>(1);
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - WhileNode, no children") {
  std::unique_ptr<TNode> node1 = std::make_unique<WhileNode>(1);
  std::unique_ptr<TNode> node2 = std::make_unique<WhileNode>(1);
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - WhileNode with children") {
  std::unique_ptr<TNode> node1 = std::make_unique<WhileNode>(1);
  node1->addChild(std::make_unique<AssignNode>(2));
  node1->addChild(std::make_unique<ReadNode>(3));
  std::unique_ptr<TNode> node2 = std::make_unique<WhileNode>(1);
  node2->addChild(std::make_unique<AssignNode>(2));
  node2->addChild(std::make_unique<ReadNode>(3));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - DivNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<DivNode>(
      std::make_unique<ConstNode>("1"), std::make_unique<ConstNode>("2"));
  std::unique_ptr<TNode> node2 = std::make_unique<DivNode>(
      std::make_unique<ConstNode>("1"), std::make_unique<ConstNode>("2"));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - MinusNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<MinusNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  std::unique_ptr<TNode> node2 = std::make_unique<MinusNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - ModNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<ModNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  std::unique_ptr<TNode> node2 = std::make_unique<ModNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - PlusNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<PlusNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  std::unique_ptr<TNode> node2 = std::make_unique<PlusNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - TimesNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<TimesNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  std::unique_ptr<TNode> node2 = std::make_unique<TimesNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - EqNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<EqNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  std::unique_ptr<TNode> node2 = std::make_unique<EqNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - NeqNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<NeqNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  std::unique_ptr<TNode> node2 = std::make_unique<NeqNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - GteNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<GteNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  std::unique_ptr<TNode> node2 = std::make_unique<GteNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - GtNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<GtNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  std::unique_ptr<TNode> node2 = std::make_unique<GtNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - LteNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<LteNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  std::unique_ptr<TNode> node2 = std::make_unique<LteNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - LtNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<LtNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  std::unique_ptr<TNode> node2 = std::make_unique<LtNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

std::unique_ptr<RelNode> makeRelNode1() {
  return std::make_unique<LteNode>(std::make_unique<VarNode>("x"),
                                   std::make_unique<ConstNode>("0"));
}

std::unique_ptr<RelNode> makeRelNode2() {
  return std::make_unique<GteNode>(std::make_unique<VarNode>("x"),
                                   std::make_unique<ConstNode>("0"));
}

TEST_CASE("Test TNode equality - AndNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<AndNode>(
      std::move(makeRelNode1()), std::move(makeRelNode2()));
  std::unique_ptr<TNode> node2 = std::make_unique<AndNode>(
      std::move(makeRelNode1()), std::move(makeRelNode2()));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - OrNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<OrNode>(
      std::move(makeRelNode1()), std::move(makeRelNode2()));
  std::unique_ptr<TNode> node2 = std::make_unique<OrNode>(
      std::move(makeRelNode1()), std::move(makeRelNode2()));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode equality - NotNode") {
  std::unique_ptr<TNode> node1 =
      std::make_unique<NotNode>(std::move(makeRelNode1()));
  std::unique_ptr<TNode> node2 =
      std::make_unique<NotNode>(std::move(makeRelNode1()));
  REQUIRE(node1->isEqual(*node2));
  REQUIRE(*node1 == *node2);
}

TEST_CASE("Test TNode inequality - VarNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<VarNode>("x");
  std::unique_ptr<TNode> node2 = std::make_unique<VarNode>("y");
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - ConstNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<VarNode>("1");
  std::unique_ptr<TNode> node2 = std::make_unique<VarNode>("2");
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - ProcNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<ProcNode>("dummy");
  std::unique_ptr<TNode> node2 = std::make_unique<ProcNode>("dummy2");
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode equality - StmtListNode, diff line number") {
  std::unique_ptr<TNode> node1 = std::make_unique<StmtListNode>();
  node1->addChild(std::make_unique<AssignNode>(1));
  node1->addChild(std::make_unique<PrintNode>(2));
  std::unique_ptr<TNode> node2 = std::make_unique<StmtListNode>();
  node2->addChild(std::make_unique<AssignNode>(1));
  node2->addChild(std::make_unique<PrintNode>(3));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - StmtNode same type, different line number") {
  std::unique_ptr<TNode> node1 = std::make_unique<AssignNode>(1);
  std::unique_ptr<TNode> node2 = std::make_unique<AssignNode>(2);
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - StmtNode different type, same line number") {
  std::unique_ptr<TNode> node1 = std::make_unique<AssignNode>(1);
  std::unique_ptr<TNode> node2 = std::make_unique<ReadNode>(1);
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE(
    "Test TNode inequality - StmtNode different type, different line number") {
  std::unique_ptr<TNode> node1 = std::make_unique<PrintNode>(1);
  std::unique_ptr<TNode> node2 = std::make_unique<ReadNode>(2);
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode equality - WhileNode with different number of children") {
  std::unique_ptr<TNode> node1 = std::make_unique<WhileNode>(1);
  node1->addChild(std::make_unique<AssignNode>(2));
  std::unique_ptr<TNode> node2 = std::make_unique<WhileNode>(1);
  node2->addChild(std::make_unique<AssignNode>(2));
  node2->addChild(std::make_unique<ReadNode>(3));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE(
    "Test TNode equality - WhileNode with same children different line "
    "number") {
  std::unique_ptr<TNode> node1 = std::make_unique<WhileNode>(1);
  node1->addChild(std::make_unique<ReadNode>(2));
  node1->addChild(std::make_unique<AssignNode>(3));
  std::unique_ptr<TNode> node2 = std::make_unique<WhileNode>(1);
  node2->addChild(std::make_unique<AssignNode>(2));
  node2->addChild(std::make_unique<ReadNode>(3));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode equality - ArithmNode different type") {
  std::unique_ptr<TNode> node1 = std::make_unique<DivNode>(
      std::make_unique<ConstNode>("1"), std::make_unique<ConstNode>("2"));
  std::unique_ptr<TNode> node2 = std::make_unique<TimesNode>(
      std::make_unique<ConstNode>("1"), std::make_unique<ConstNode>("2"));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - MinusNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<MinusNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  std::unique_ptr<TNode> node2 = std::make_unique<MinusNode>(
      std::make_unique<VarNode>("x"), std::make_unique<VarNode>("y"));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - ModNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<ModNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  std::unique_ptr<TNode> node2 = std::make_unique<ModNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<VarNode>("x"));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - PlusNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<PlusNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  std::unique_ptr<TNode> node2 = std::make_unique<PlusNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("1"));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - TimesNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<TimesNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("1"));
  std::unique_ptr<TNode> node2 = std::make_unique<TimesNode>(
      std::make_unique<ConstNode>("2"), std::make_unique<ConstNode>("2"));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - RelNode different type") {
  std::unique_ptr<TNode> node1 = std::make_unique<EqNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  std::unique_ptr<TNode> node2 = std::make_unique<NeqNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - NeqNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<NeqNode>(
      std::make_unique<VarNode>("x"), std::make_unique<VarNode>("y"));
  std::unique_ptr<TNode> node2 = std::make_unique<NeqNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - GteNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<GteNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  std::unique_ptr<TNode> node2 = std::make_unique<GteNode>(
      std::make_unique<VarNode>("x"), std::make_unique<VarNode>("y"));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - GtNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<GtNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  std::unique_ptr<TNode> node2 = std::make_unique<GtNode>(
      std::make_unique<VarNode>("y"), std::make_unique<ConstNode>("1"));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - LteNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<LteNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  std::unique_ptr<TNode> node2 = std::make_unique<LteNode>(
      std::make_unique<VarNode>("y"), std::make_unique<ConstNode>("0"));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - LtNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<LtNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("0"));
  std::unique_ptr<TNode> node2 = std::make_unique<LtNode>(
      std::make_unique<VarNode>("x"), std::make_unique<ConstNode>("1"));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - AndNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<AndNode>(
      std::move(makeRelNode1()), std::move(makeRelNode2()));
  std::unique_ptr<TNode> node2 = std::make_unique<AndNode>(
      std::move(makeRelNode2()), std::move(makeRelNode1()));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}

TEST_CASE("Test TNode inequality - OrNode") {
  std::unique_ptr<TNode> node1 = std::make_unique<OrNode>(
      std::move(makeRelNode1()), std::move(makeRelNode2()));
  std::unique_ptr<TNode> node2 = std::make_unique<OrNode>(
      std::move(makeRelNode2()), std::move(makeRelNode1()));
  REQUIRE(!node1->isEqual(*node2));
  REQUIRE(*node1 != *node2);
}
