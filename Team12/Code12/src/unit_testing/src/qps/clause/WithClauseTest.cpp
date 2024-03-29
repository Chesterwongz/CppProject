#include <catch.hpp>

#include "../../unit_testing/src/qps/mocks/MockPKBReader.h"
#include "../../unit_testing/src/qps/mocks/mockReaders/MockDesignEntitiesReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/withClause/WithClause.h"
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

  WithClause withClause1 =
      WithClause(std::move(withSynonymPtr1), std::move(integerPtr1));

  unique_ptr<SynonymArg> withSynonymPtr2 =
      std::make_unique<SynonymArg>(withSynonymArgVal, synonymEntity, attrRef);

  unique_ptr<Integer> integerPtr2 = std::make_unique<Integer>(attrRefValue);

  WithClause withClause2 =
      WithClause(std::move(withSynonymPtr2), std::move(integerPtr2));

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStatements = {"1", "2", "3", "99"};

  mockPkbReader.mockStatements = mockStatements;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();
  TableDataType expectedData = {
      {SynonymResFactory::buildStmtSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStatements = {"1", "2", "3", "100"};  // no 99

  mockPkbReader.mockStatements = mockStatements;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockVarReadBy = {"yes"};
  mockPkbReader.mockVariableReadBy = mockVarReadBy;

  vector<pair<string, string>> mockStmtVarReadPairs = {
      {"1", "yes"}, {"2", "lol"}, {"98", "yes"}};
  mockPkbReader.mockStmtReadPairs = mockStmtVarReadPairs;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();
  TableDataType expectedData = {
      {SynonymResFactory::buildReadSynonym(attrRefValue, mockVarReadBy[0])}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  mockPkbReader.mockVariableReadBy = {};

  vector<pair<string, string>> mockStmtVarReadPairs = {
      {"1", "yes"}, {"2", "lol"}, {"100", "yes"}};  // no 98
  mockPkbReader.mockStmtReadPairs = mockStmtVarReadPairs;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStatementsThatRead = {"1", "2", "3"};
  mockPkbReader.mockStatmentsThatRead = mockStatementsThatRead;

  vector<pair<string, string>> mockStmtVarReadPairs = {
      {"1", "yes"}, {"2", "readMe"}, {"3", "yes"}};
  mockPkbReader.mockStmtReadPairs = mockStmtVarReadPairs;

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
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStatementsThatRead = {};
  mockPkbReader.mockStatmentsThatRead = mockStatementsThatRead;

  vector<pair<string, string>> mockStmtVarReadPairs = {
      {"1", "yes"}, {"2", "notreadMe"}, {"3", "yes"}};
  mockPkbReader.mockStmtReadPairs = mockStmtVarReadPairs;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockVarPrintedBy = {"IWASPRINTED"};
  mockPkbReader.mockVariablePrintedBy = mockVarPrintedBy;

  vector<pair<string, string>> stmtVarPrintPairs = {{"1", "hi"},
                                                    {"97", "IWASPRINTED"}};
  mockPkbReader.mockStmtVarPrintPairs = stmtVarPrintPairs;

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
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockVarPrintedBy = {};
  mockPkbReader.mockVariablePrintedBy = mockVarPrintedBy;

  vector<pair<string, string>> stmtVarPrintPairs = {{"1", "hi"},
                                                    {"98", "IWASPRINTED"}};
  mockPkbReader.mockStmtVarPrintPairs = stmtVarPrintPairs;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStmtsThatPrint = {"4", "5", "6"};
  mockPkbReader.mockStatementsThatPrint = mockStmtsThatPrint;

  vector<pair<string, string>> stmtVarPrintPairs = {
      {"4", "printMe"}, {"5", "printMe"}, {"6", "DONTPRINTME"}};
  mockPkbReader.mockStmtVarPrintPairs = stmtVarPrintPairs;

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
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStmtsThatPrint = {};
  mockPkbReader.mockStatementsThatPrint = mockStmtsThatPrint;

  vector<pair<string, string>> stmtVarPrintPairs = {
      {"4", "printMeee"}, {"5", "printMee4"}, {"6", "DONTPRINTME"}};
  mockPkbReader.mockStmtVarPrintPairs = stmtVarPrintPairs;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockProcNameCalledByStmtNum = {"iWasCalled"};
  mockPkbReader.mockProcNameCalledByStmtNum = mockProcNameCalledByStmtNum;

  vector<pair<string, string>> stmtProcCallsPairs = {
      {"1", "sjdnf"}, {"96", "iWasCalled"}, {"100", "skjdf"}};
  mockPkbReader.mockStmtProcCallsPairs = stmtProcCallsPairs;

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
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockProcNameCalledByStmtNum = {};
  mockPkbReader.mockProcNameCalledByStmtNum = mockProcNameCalledByStmtNum;

  vector<pair<string, string>> stmtProcCallsPairs = {
      {"1", "sjdnf"}, {"99", "iWasCalled"}, {"100", "skjdf"}};
  mockPkbReader.mockStmtProcCallsPairs = stmtProcCallsPairs;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStmtsThatCall = {"7"};
  mockPkbReader.mockStatementsThatCall = mockStmtsThatCall;

  vector<pair<string, string>> stmtProcCallsPairs = {
      {"7", "plsCallMe"}, {"8", "iWasCalled"}, {"9", "skjdf"}};
  mockPkbReader.mockStmtProcCallsPairs = stmtProcCallsPairs;

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
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> mockStmtsThatCall = {};
  mockPkbReader.mockStatementsThatCall = mockStmtsThatCall;

  vector<pair<string, string>> stmtProcCallsPairs = {
      {"7", "CallMe"}, {"8", "iWasCalled"}, {"9", "skjdf"}};
  mockPkbReader.mockStmtProcCallsPairs = stmtProcCallsPairs;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allStmtsOf = {"1", "2", "3", "4", "95"};
  mockPkbReader.mockStatements = allStmtsOf;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();

  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildStmtSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allStmtsOf = {"1", "2", "3", "4"};
  mockPkbReader.mockStatements = allStmtsOf;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allStmtsOf = {"1", "2", "3", "4", "94"};
  mockPkbReader.mockStatements = allStmtsOf;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();
  TableDataType expectedData = {
      {SynonymResFactory::buildStmtSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allStmtsOf = {"1", "2", "3", "4"};
  mockPkbReader.mockStatements = allStmtsOf;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allStmtsOf = {"1", "2", "3", "4", "93"};
  mockPkbReader.mockStatements = allStmtsOf;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildStmtSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allStmtsOf = {"1", "2", "3", "4"};
  mockPkbReader.mockStatements = allStmtsOf;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allVariables = {"a", "b", "imAVariable", "c"};
  mockPkbReader.mockAllVariables = allVariables;
  mockPkbReader.mockIsValidVariable = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildVarSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allVariables = {"a", "b", "imNotAVariable", "c"};
  mockPkbReader.mockAllVariables = allVariables;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allConstants = {"1", "2", "3", "93"};
  mockPkbReader.mockAllConstants = allConstants;
  mockPkbReader.mockIsValidConstant = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildConstantSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allConstants = {"1", "2", "3", "92"};
  mockPkbReader.mockAllConstants = allConstants;

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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allProcs = {"sdf", "sdre", "theBestProc", "lousy"};
  mockPkbReader.mockAllProcedures = allProcs;
  mockPkbReader.mockIsValidProcName = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildProcSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(isTableDataSame(actualTableData, expectedData));
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

  WithClause withClause =
      WithClause(std::move(withSynonymPtr), std::move(valueArgPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allProcs = {"sdf", "sdre", "lousy"};
  mockPkbReader.mockAllProcedures = allProcs;

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

  vector<string> allProcs = {"sdf", "sdre", "theBestProc", "lousy"};
  mockPkbReader.mockAllProcedures = allProcs;
  mockPkbReader.mockIsValidProcName = true;

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getTableData();

  TableDataType expectedData = {
      {SynonymResFactory::buildProcSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonymArgVal);
  REQUIRE(isTableDataSame(actualTableData, expectedData));
}

TEST_CASE(
    "test_withClause_evaluate_PROCEDURE_PROCNAME_permutation_swapArgs_"
    "noResults") {
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

TEST_CASE(
    "test_withClause_evaluate_proc.procName = "
    "call.procName_"
    "joinOnDifferentColNameButSameAttr") {
  // procedure proc call call; select proc with proc.procName = call.procName
  string withProcSynonymArgVal = "proc";
  Entity procSynonymEntity = PROCEDURE_ENTITY;
  AttrRef procAttrRef = ATTR_REF_PROC_NAME;
  // string procAttrRefValue = "theBestProc";

  string withCallSynonymArgVal = "call";
  Entity callSynonymEntity = CALL_ENTITY;
  AttrRef callAttrRef = ATTR_REF_PROC_NAME;

  unique_ptr<SynonymArg> withProcSynonymPtr = std::make_unique<SynonymArg>(
      withProcSynonymArgVal, procSynonymEntity, procAttrRef);

  unique_ptr<SynonymArg> withCallSynonymPtr = std::make_unique<SynonymArg>(
      withCallSynonymArgVal, callSynonymEntity, callAttrRef);

  WithClause withClause =
      WithClause(std::move(withProcSynonymPtr), std::move(withCallSynonymPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allProcs = {"p1", "p2"};
  mockPkbReader.mockAllProcedures = allProcs;

  vector<pair<string, string>> stmtProcCallsPairs = {
      {"1", "p1"}, {"96", "p2"}, {"101", "p1"}};
  mockPkbReader.mockStmtProcCallsPairs = stmtProcCallsPairs;

  SynonymRes proc1 = SynonymResFactory::buildProcSynonym("p1");
  SynonymRes proc2 = SynonymResFactory::buildProcSynonym("p2");

  SynonymRes call1 = SynonymResFactory::buildCallsSynonym("1", "p1");
  SynonymRes call2 = SynonymResFactory::buildCallsSynonym("96", "p2");
  SynonymRes call3 = SynonymResFactory::buildCallsSynonym("101", "p1");

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);
  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualData = actualTable.getTableData();
  int actualRowCount = actualTable.getRowCount();

  TableDataType expectedData = {{proc1, call1}, {proc1, call3}, {proc2, call2}};

  REQUIRE(actualColNames.size() == 2);
  REQUIRE(actualColNames[0] == withProcSynonymArgVal);
  REQUIRE(actualColNames[1] == withCallSynonymArgVal);
  REQUIRE(actualRowCount == 3);
  REQUIRE(isTableDataSame(actualData, expectedData));
}

TEST_CASE(
    "test_withClause_evaluate_a.stmt# = "
    "a.stmt#_"
    "joinOnSameColNameAndAttr") {
  // assign a; select a with a.stmt# = a.stmt#
  string assignSynonymArgVal = "a";
  Entity assignSynonymEntity = ASSIGN_ENTITY;
  AttrRef assignAttrRef = ATTR_REF_STMT_NUMBER;

  unique_ptr<SynonymArg> withAssignSynonymPtr1 = std::make_unique<SynonymArg>(
      assignSynonymArgVal, assignSynonymEntity, assignAttrRef);

  unique_ptr<SynonymArg> withAssignSynonymPtr2 = std::make_unique<SynonymArg>(
      assignSynonymArgVal, assignSynonymEntity, assignAttrRef);

  WithClause withClause = WithClause(std::move(withAssignSynonymPtr1),
                                     std::move(withAssignSynonymPtr2));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allStmtsOf = {"1", "2", "4", "8"};
  mockPkbReader.mockStatements = allStmtsOf;

  SynonymRes assign1 = SynonymResFactory::buildStmtSynonym("1");
  SynonymRes assign2 = SynonymResFactory::buildStmtSynonym("2");
  SynonymRes assign3 = SynonymResFactory::buildStmtSynonym("4");
  SynonymRes assign4 = SynonymResFactory::buildStmtSynonym("8");

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);
  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualData = actualTable.getTableData();
  int actualRowCount = actualTable.getRowCount();

  TableDataType expectedData = {{assign1}, {assign2}, {assign3}, {assign4}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == assignSynonymArgVal);
  REQUIRE(actualRowCount == 4);
  REQUIRE(isTableDataSame(actualData, expectedData));
}

TEST_CASE(
    "test_withClause_evaluate_c.varName = "
    "p.procName_"
    "joinOnDifferentColNameAndDifferentAttr") {
  // variable v; proc p; Select v with v.varName = p.procName
  string varSynonymArgVal = "v";
  Entity varSynonymEntity = VARIABLE_ENTITY;
  AttrRef varAttrRef = ATTR_REF_VAR_NAME;

  string procSynonymArgVal = "p";
  Entity procSynonymEntity = PROCEDURE_ENTITY;
  AttrRef procAttrRef = ATTR_REF_PROC_NAME;

  unique_ptr<SynonymArg> withVarSynonymPtr = std::make_unique<SynonymArg>(
      varSynonymArgVal, varSynonymEntity, varAttrRef);

  unique_ptr<SynonymArg> withProcSynonymPtr = std::make_unique<SynonymArg>(
      procSynonymArgVal, procSynonymEntity, procAttrRef);

  WithClause withClause =
      WithClause(std::move(withVarSynonymPtr), std::move(withProcSynonymPtr));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<string> allVars = {"p1", "p2", "p3"};
  mockPkbReader.mockAllVariables = allVars;

  vector<string> allProcs = {"p1", "p2"};
  mockPkbReader.mockAllProcedures = allProcs;

  SynonymRes var1 = SynonymResFactory::buildVarSynonym("p1");
  SynonymRes var2 = SynonymResFactory::buildVarSynonym("p2");
  SynonymRes var3 = SynonymResFactory::buildVarSynonym("p3");

  SynonymRes proc1 = SynonymResFactory::buildVarSynonym("p1");
  SynonymRes proc2 = SynonymResFactory::buildVarSynonym("p2");

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);
  vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualData = actualTable.getTableData();
  int actualRowCount = actualTable.getRowCount();

  TableDataType expectedData = {{var1, proc1}, {var2, proc2}};

  REQUIRE(actualColNames.size() == 2);
  REQUIRE(actualColNames[0] == varSynonymArgVal);
  REQUIRE(actualColNames[1] == procSynonymArgVal);
  REQUIRE(actualRowCount == 2);
  REQUIRE(isTableDataSame(actualData, expectedData));
}

TEST_CASE(
    "test_withClause_evaluate_c.varName = "
    "p.procName_"
    "joinOnSameColNameButDifferentAttr") {
  // variable v; proc p; Select v with v.varName = p.procName
  string callSynonymArgVal = "c";
  Entity callSynonymEntity = VARIABLE_ENTITY;
  AttrRef callAttrRef1 = ATTR_REF_STMT_NUMBER;
  AttrRef callAttrRef2 = ATTR_REF_PROC_NAME;

  unique_ptr<SynonymArg> withCallSynonymPtr1 = std::make_unique<SynonymArg>(
      callSynonymArgVal, callSynonymEntity, callAttrRef1);

  unique_ptr<SynonymArg> withCallSynonymPtr2 = std::make_unique<SynonymArg>(
      callSynonymArgVal, callSynonymEntity, callAttrRef2);

  WithClause withClause = WithClause(std::move(withCallSynonymPtr1),
                                     std::move(withCallSynonymPtr2));

  MockDesignEntitiesReader mockPkbReader = MockDesignEntitiesReader();

  vector<pair<string, string>> stmtProcCallsPairs = {
      {"1", "p1"}, {"99", "p2"}, {"100", "p3"}};
  mockPkbReader.mockStmtProcCallsPairs = stmtProcCallsPairs;

  SynonymRes call1 = SynonymResFactory::buildCallsSynonym("1", "pq");
  SynonymRes call2 = SynonymResFactory::buildCallsSynonym("99", "p2");
  SynonymRes call3 = SynonymResFactory::buildCallsSynonym("100", "p3");

  IntermediateTable actualTable = withClause.evaluate(mockPkbReader);

  REQUIRE(actualTable.isTableEmpty());
}
