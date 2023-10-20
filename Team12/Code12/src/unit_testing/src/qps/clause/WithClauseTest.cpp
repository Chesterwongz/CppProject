#include <catch.hpp>

#include "../../unit_testing/src/qps/mocks/MockPKBReader.h"
#include "../../unit_testing/src/qps/mocks/mockReaders/MockDesignEntitiesReader.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/ident/Ident.h"
#include "qps/clause/withClause/WithClause.h"
#include "qps/clause/withClause/WithClauseUtils.h"
#include "qps/common/Keywords.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/intermediateTable/synonymRes/SynonymResFactory.h"

using std::unique_ptr, std::make_unique, std::string;

TEST_CASE("test_withClause_isEqual") {
  string withSynonymArgVal = "w";
  Entity synonymEntity = WHILE_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "100";

  unique_ptr<SynonymArg> withSynonymPtr1 =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> integerPtr1 = std::make_unique<Integer>(attrRefValue);

  WithClause withClause1 = WithClause(std::move(withSynonymPtr1), std::move(integerPtr1));

  unique_ptr<SynonymArg> withSynonymPtr2 =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> integerPtr2 = std::make_unique<Integer>(attrRefValue);

  WithClause withClause2 = WithClause(std::move(withSynonymPtr2), std::move(integerPtr2));

  REQUIRE(withClause1.isEquals(withClause2));
  REQUIRE(withClause2.isEquals(withClause1));
}

TEST_CASE("test_withClause_evaluate_STMT_STMTNUM_permutation") {
  // stmt s; select s with s.stmt# = 99
  string withSynonymArgVal = "s";
  Entity synonymEntity = STMT_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "99";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidStatement = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();
  TableDataType expectedData = {
      {SynonymResFactory::buildStmtSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_STMT_STMTNUM_permutation_noResults") {
  // stmt s; select s with s.stmt# = 99
  string withSynonymArgVal = "s";
  Entity synonymEntity = STMT_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "99";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidStatement = false;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_READ_STMTNUM_permutation") {
  // read r; select r with r.stmt# = 98
  string withSynonymArgVal = "r";
  Entity synonymEntity = READ_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "98";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockVarReadBy = {"yes"};
  mockPkbReader.mockVariableReadBy = mockVarReadBy;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();
  TableDataType expectedData = {
      {SynonymResFactory::buildReadSynonym(attrRefValue, mockVarReadBy[0])}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_read_STMTNUM_permutation_noResults") {
  // read r; select r with r.stmt# = 98
  string withSynonymArgVal = "r";
  Entity synonymEntity = READ_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "98";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockVariableReadBy = {};

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_READ_VARNAME_permutation") {
  // read r; select r with r.varName = readMe
  string withSynonymArgVal = "r";
  Entity synonymEntity = READ_ENTITY;
  AttrRef attrRef = ATTR_REF_VAR_NAME;
  string attrRefValue = "readMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);
  
  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStatementsThatRead = {"1", "2", "3"};
  mockPkbReader.mockStatmentsThatRead = mockStatementsThatRead;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();
  TableDataType expectedData;

  for (int i = 0; i < mockStatementsThatRead.size(); i++) {
    expectedData.push_back({SynonymResFactory::buildReadSynonym(
        mockStatementsThatRead[i], attrRefValue)});
  }

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_READ_VARNAME_permutation_noResults") {
  // read r; select r with r.varName = readMe
  string withSynonymArgVal = "r";
  Entity synonymEntity = READ_ENTITY;
  AttrRef attrRef = ATTR_REF_VAR_NAME;
  string attrRefValue = "readMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStatementsThatRead = {};
  mockPkbReader.mockStatmentsThatRead = mockStatementsThatRead;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_PRINT_STMTNUM_permutation") {
  // print p; select p with p.stmmt# = 97
  string withSynonymArgVal = "p";
  Entity synonymEntity = PRINT_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "97";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockVarPrintedBy = {"IWASPRINTED"};
  mockPkbReader.mockVariablePrintedBy = mockVarPrintedBy;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData;

  for (int i = 0; i < mockVarPrintedBy.size(); i++) {
    expectedData.push_back({SynonymResFactory::buildPrintSynonym(
        attrRefValue, mockVarPrintedBy[i])});
  }

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_PRINT_STMTNUM_permutation_noResults") {
  // print p; select p with p.stmmt# = 97
  string withSynonymArgVal = "p";
  Entity synonymEntity = PRINT_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "97";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockVarPrintedBy = {};
  mockPkbReader.mockVariablePrintedBy = mockVarPrintedBy;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_PRINT_VARNAME_permutation") {
  // print p; select p with p.varName = printMe
  string withSynonymArgVal = "p";
  Entity synonymEntity = PRINT_ENTITY;
  AttrRef attrRef = ATTR_REF_VAR_NAME;
  string attrRefValue = "printMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStmtsThatPrint = {"4", "5", "6"};
  mockPkbReader.mockStatementsThatPrint = mockStmtsThatPrint;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();
  TableDataType expectedData;
  for (int i = 0; i < mockStmtsThatPrint.size(); i++) {
    expectedData.push_back({SynonymResFactory::buildPrintSynonym(
        mockStmtsThatPrint[i], attrRefValue)});
  }

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_PRINT_VARNAME_permutation_noResults") {
  // print p; select p with p.varName = printMe
  string withSynonymArgVal = "p";
  Entity synonymEntity = PRINT_ENTITY;
  AttrRef attrRef = ATTR_REF_VAR_NAME;
  string attrRefValue = "printMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStmtsThatPrint = {};
  mockPkbReader.mockStatementsThatPrint = mockStmtsThatPrint;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_CALL_STMTNUM_permutation") {
  // call c; select c with c.stmt# = 96
  string withSynonymArgVal = "c";
  Entity synonymEntity = CALL_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "96";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockProcNameCalledByStmtNum = {"iWasCalled"};
  mockPkbReader.mockProcNameCalledByStmtNum = mockProcNameCalledByStmtNum;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData;

  for (int i = 0; i < mockProcNameCalledByStmtNum.size(); i++) {
    expectedData.push_back({SynonymResFactory::buildCallsSynonym(
        attrRefValue, mockProcNameCalledByStmtNum[i])});
  }

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_CALL_STMTNUM_permutation_noResults") {
  // call c; select c with c.stmt# = 96
  string withSynonymArgVal = "c";
  Entity synonymEntity = CALL_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "96";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockProcNameCalledByStmtNum = {};
  mockPkbReader.mockProcNameCalledByStmtNum = mockProcNameCalledByStmtNum;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_CALL_PROCNAME_permutation") {
  // call c; select c with c.procName = plsCallMe
  string withSynonymArgVal = "c";
  Entity synonymEntity = CALL_ENTITY;
  AttrRef attrRef = ATTR_REF_PROC_NAME;
  string attrRefValue = "plsCallMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);
  
  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStmtsThatCall = {"7", "8", "9"};
  mockPkbReader.mockStatementsThatCall = mockStmtsThatCall;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData;

  for (int i = 0; i < mockStmtsThatCall.size(); i++) {
    expectedData.push_back({SynonymResFactory::buildCallsSynonym(
        mockStmtsThatCall[i], attrRefValue)});
  }

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_CALL_PROCNAME_permutation_noResults") {
  // call c; select c with c.procName = plsCallMe
  string withSynonymArgVal = "c";
  Entity synonymEntity = CALL_ENTITY;
  AttrRef attrRef = ATTR_REF_PROC_NAME;
  string attrRefValue = "plsCallMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStmtsThatCall = {};
  mockPkbReader.mockStatementsThatCall = mockStmtsThatCall;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_WHILE_STMTNUM_permutation") {
  // while w; select w with w.stmt# = 95
  string withSynonymArgVal = "w";
  Entity synonymEntity = WHILE_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "95";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidStatement = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();

  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildStmtSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_WHILE_STMTNUM_permutation_noResults") {
  // while w; select w with w.stmt# = 95
  string withSynonymArgVal = "w";
  Entity synonymEntity = WHILE_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "95";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidStatement = false;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_IF_STMTNUM_permutation") {
  // if i; select i with i.stmt# = 94
  string withSynonymArgVal = "i";
  Entity synonymEntity = IF_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "94";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidStatement = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();
  TableDataType expectedData = {
      {SynonymResFactory::buildStmtSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_IF_STMTNUM_permutation_noResults") {
  // if i; select i with i.stmt# = 94
  string withSynonymArgVal = "i";
  Entity synonymEntity = IF_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "94";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidStatement = false;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_ASSIGN_STMTNUM_permutation") {
  // assign a; select a with a.stmt# = 93
  string withSynonymArgVal = "a";
  Entity synonymEntity = ASSIGN_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "93";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidStatement = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildStmtSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_ASSIGN_STMTNUM_permutation_noResults") {
  // assign a; select a with a.stmt# = 93
  string withSynonymArgVal = "a";
  Entity synonymEntity = ASSIGN_ENTITY;
  AttrRef attrRef = ATTR_REF_STMT_NUMBER;
  string attrRefValue = "93";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidStatement = false;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_VAR_VARNAME_permutation") {
  // variable v; select v with v.varName = "imAVariable"
  string withSynonymArgVal = "v";
  Entity synonymEntity = VARIABLE_ENTITY;
  AttrRef attrRef = ATTR_REF_VAR_NAME;
  string attrRefValue = "imAVariable";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidVariable = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildVarSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_VAR_VARNAME_permutation_noResults") {
  // variable v; select v with v.varName = "imAVariable"
  string withSynonymArgVal = "v";
  Entity synonymEntity = VARIABLE_ENTITY;
  AttrRef attrRef = ATTR_REF_VAR_NAME;
  string attrRefValue = "imAVariable";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidVariable = false;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_CONSTANT_VALUE_permutation") {
  // constant const; select const with const.value = 93
  string withSynonymArgVal = "const";
  Entity synonymEntity = CONSTANT_ENTITY;
  AttrRef attrRef = ATTR_REF_VALUE;
  string attrRefValue = "93";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidConstant = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildConstantSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_CONSTANT_VALUE_permutation_noResults") {
  // constant const; select const with const.value = 93
  string withSynonymArgVal = "const";
  Entity synonymEntity = CONSTANT_ENTITY;
  AttrRef attrRef = ATTR_REF_VALUE;
  string attrRefValue = "93";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> valueArgPtr = std::make_unique<Integer>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidConstant = false;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_PROCEDURE_PROCNAME_permutation") {
  // procedure proc; select proc with proc.procName = "theBestProc"
  string withSynonymArgVal = "proc";
  Entity synonymEntity = PROCEDURE_ENTITY;
  AttrRef attrRef = ATTR_REF_PROC_NAME;
  string attrRefValue = "theBestProc";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidProcName = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildProcSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_PROCEDURE_PROCNAME_permutation_noResults") {
  // procedure proc; select proc with proc.procName = "theBestProc"
  string withSynonymArgVal = "proc";
  Entity synonymEntity = PROCEDURE_ENTITY;
  AttrRef attrRef = ATTR_REF_PROC_NAME;
  string attrRefValue = "theBestProc";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);

  WithClause withClause = WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  
  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidProcName = false;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_PROCEDURE_PROCNAME_permutation_swapArgs") {
  // procedure proc; select proc with "theBestProc" = proc.procName
  string withSynonymArgVal = "proc";
  Entity synonymEntity = PROCEDURE_ENTITY;
  AttrRef attrRef = ATTR_REF_PROC_NAME;
  string attrRefValue = "theBestProc";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);

  // swapped the args - synonymPtr is now second
  WithClause withClause =
      WithClause(std::move(valueArgPtr), std::move(withSynonymPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidProcName = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildProcSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_withClause_evaluate_PROCEDURE_PROCNAME_permutation_swapArgs_noResults") {
  // procedure proc; select proc with "theBestProc" = proc.procName
  string withSynonymArgVal = "proc";
  Entity synonymEntity = PROCEDURE_ENTITY;
  AttrRef attrRef = ATTR_REF_PROC_NAME;
  string attrRefValue = "theBestProc";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Ident> valueArgPtr = std::make_unique<Ident>(attrRefValue);

  // swapped the args - synonymPtr is now second
  WithClause withClause =
      WithClause(std::move(valueArgPtr), std::move(withSynonymPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockIsValidProcName = false;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_ident = ident_wildcardTable") {
  // with hello = hello
  string attrRefValue = "hello";

  unique_ptr<Ident> valueArgPtr1 = std::make_unique<Ident>(attrRefValue);
  unique_ptr<Ident> valueArgPtr2 = std::make_unique<Ident>(attrRefValue);

  WithClause withClause =
      WithClause(std::move(valueArgPtr1), std::move(valueArgPtr2));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableWildcard());
}

TEST_CASE("test_withClause_evaluate_ident = ident_emptyTable") {
  // with hello = goodbye
  string attrRefValue1 = "hello";
  string attrRefValue2 = "goodbye";

  unique_ptr<Ident> valueArgPtr1 = std::make_unique<Ident>(attrRefValue1);
  unique_ptr<Ident> valueArgPtr2 = std::make_unique<Ident>(attrRefValue2);

  WithClause withClause =
      WithClause(std::move(valueArgPtr1), std::move(valueArgPtr2));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_int = int_wildcardTable") {
  // with 2 = 2
  string attrRefValue = "2";

  unique_ptr<Integer> valueArgPtr1 = std::make_unique<Integer>(attrRefValue);
  unique_ptr<Integer> valueArgPtr2 = std::make_unique<Integer>(attrRefValue);

  WithClause withClause =
      WithClause(std::move(valueArgPtr1), std::move(valueArgPtr2));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableWildcard());
}

TEST_CASE("test_withClause_evaluate_int = int_emptyTable") {
  // with 2 = 3
  string attrRefValue1 = "2";
  string attrRefValue2 = "3";

  unique_ptr<Integer> valueArgPtr1 = std::make_unique<Integer>(attrRefValue1);
  unique_ptr<Integer> valueArgPtr2 = std::make_unique<Integer>(attrRefValue2);

  WithClause withClause =
      WithClause(std::move(valueArgPtr1), std::move(valueArgPtr2));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_int = ident_emptyTable") {
  // with 2 = 3
  string attrRefValue1 = "2";
  string attrRefValue2 = "bruv";

  unique_ptr<Integer> valueArgPtr1 = std::make_unique<Integer>(attrRefValue1);
  unique_ptr<Ident> valueArgPtr2 = std::make_unique<Ident>(attrRefValue2);

  WithClause withClause =
      WithClause(std::move(valueArgPtr1), std::move(valueArgPtr2));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}
