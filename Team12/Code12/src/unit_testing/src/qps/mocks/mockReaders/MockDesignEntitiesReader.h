#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "MockModifiesReader.h"
#include "pkb/facade/PKBReader.h"

using std::vector, std::set, std::string, std::pair;

class MockDesignEntitiesReader : public BaseMockReader {
 public:
  bool mockIsValidStatement {};
  bool mockIsValidVariable {};
  bool mockIsValidConstant {};
  bool mockIsValidProcName {};
  vector<string> mockVariableReadBy;
  vector<string> mockStatmentsThatRead;
  vector<string> mockVariablePrintedBy;
  vector<string> mockStatementsThatPrint;
  vector<string> mockProcNameCalledByStmtNum;
  vector<string> mockStatementsThatCall;

  MockDesignEntitiesReader() : BaseMockReader() {}

  bool isValidStmt(int stmtNum, StmtType stmtType) override {
    return mockIsValidStatement;
  }

  bool isValidVariable(string varName) override { return mockIsValidVariable; }

  bool isValidConstant(string constantValue) override {
    return mockIsValidConstant;
  }

  bool isValidProc(string procName) override { return mockIsValidProcName; }

  vector<string> getVariableReadBy(int stmtNum) override {
    return mockVariableReadBy;
  }

  vector<string> getStmtsThatRead(const string& varName) override {
    return mockStatmentsThatRead;
  }

  vector<string> getVariablePrintedBy(int stmtNum) override {
    return mockVariablePrintedBy;
  }

  vector<string> getStmtsThatPrint(const string& varName) override {
    return mockStatementsThatPrint;
  }

  vector<string> getProcCalledBy(int stmtNum) override {
    return mockProcNameCalledByStmtNum;
  }

  vector<string> getStmtsThatCall(const string& procName) override {
    return mockStatementsThatCall;
  }
};
