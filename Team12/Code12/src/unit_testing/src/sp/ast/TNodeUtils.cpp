#include "TNodeUtils.h"

unique_ptr<ProgramNode> makeProgramNode() { return make_unique<ProgramNode>(); }

unique_ptr<ProcNode> makeProcedureNode(const string& procName) {
  return make_unique<ProcNode>(procName);
}

unique_ptr<ReadNode> makeReadNode(int lineNum, const string& varName) {
  unique_ptr<ReadNode> readNode = make_unique<ReadNode>(lineNum);
  readNode->addChild(make_unique<VarNode>(varName));
  return readNode;
}

unique_ptr<PrintNode> makePrintNode(int lineNum, const string& varName) {
  unique_ptr<PrintNode> printNode = make_unique<PrintNode>(lineNum);
  printNode->addChild(make_unique<VarNode>(varName));
  return printNode;
}

unique_ptr<AssignNode> makeAssignWithPlusNode(int lineNum,
                                              const string& leftVar,
                                              const string& rightVar,
                                              const string& constValue) {
  unique_ptr<AssignNode> assignNode = make_unique<AssignNode>(lineNum);
  assignNode->addChild(make_unique<VarNode>(leftVar));
  unique_ptr<PlusNode> plusNode = make_unique<PlusNode>(
      make_unique<VarNode>(rightVar), make_unique<ConstNode>(constValue));
  assignNode->addChild(std::move(plusNode));
  return assignNode;
}

unique_ptr<LtNode> makeLtNode(const string& leftVar, const string& rightVar) {
  return make_unique<LtNode>(make_unique<VarNode>(leftVar),
                             make_unique<VarNode>(rightVar));
}

unique_ptr<EqNode> makeEqNode(const string& leftVar, const string& rightVar) {
  return make_unique<EqNode>(make_unique<VarNode>(leftVar),
                             make_unique<VarNode>(rightVar));
}