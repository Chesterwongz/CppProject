#include <catch.hpp>

#include "../../unit_testing/src/qps/mocks/MockContext.h"
#include "../../unit_testing/src/qps/mocks/MockPKBReader.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/withClause/WithClause.h"
#include "qps/clause/withClause/WithClauseUtils.h"
#include "qps/common/Keywords.h"
// TODO(houten): include synonymRes

using std::unique_ptr, std::make_unique, std::string;

TEST_CASE("test_withClause_isEqual") {
  SynonymArg withSynonym = SynonymArg("w");
  Entity synonymEntity = WHILE_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "100";

  unique_ptr<SynonymArg> withSynonymPtr1 =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause1 = WithClause(std::move(withSynonymPtr1), synonymEntity,
                                      attrRef, attrRefValue);

  unique_ptr<SynonymArg> withSynonymPtr2 =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause2 = WithClause(std::move(withSynonymPtr2), synonymEntity,
                                      attrRef, attrRefValue);

  REQUIRE(withClause1.isEquals(withClause2));
  REQUIRE(withClause2.isEquals(withClause1));
}

TEST_CASE("test_withClause_evaluate_STMT_STMTNUM_permutation") {
  // stmt s; select s with s.stmt# = 99
  SynonymArg withSynonym = SynonymArg("s");
  Entity synonymEntity = STMT_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "99";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidStatement = true;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData =
  {{SynonymResFactory::buildStmtSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_STMT_STMTNUM_permutation_noResults") {
  // stmt s; select s with s.stmt# = 99
  SynonymArg withSynonym = SynonymArg("s");
  Entity synonymEntity = STMT_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "99";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidStatement = false;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_READ_STMTNUM_permutation") {
  // read r; select r with r.stmt# = 98
  SynonymArg withSynonym = SynonymArg("r");
  Entity synonymEntity = READ_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "98";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockVariableReadBy = {"yes"};

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData =
  {{SynonymResFactory::buildReadSynonym(attrRefValue,
  mockPkbReader.variableReadBy)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_read_STMTNUM_permutation_noResults") {
  // read r; select r with r.stmt# = 98
  SynonymArg withSynonym = SynonymArg("r");
  Entity synonymEntity = READ_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "98";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockVariableReadBy = {""};

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_READ_VARNAME_permutation") {
  // read r; select r with r.varName = readMe
  SynonymArg withSynonym = SynonymArg("r");
  Entity synonymEntity = READ_ENTITY;
  AttrRef attrRef = VARNAME_ATTRREF;
  string attrRefValue = "readMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  vector<string> mockStatementsThatRead = {"1", "2", "3"};
  mockPkbReader.mockStatmentsThatRead = mockStatementsThatRead;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData;
  for (int i = 0; i < mockStatementsThatRead.size(); i++) {
    expectedData.push_back(SynonymResFactory::buildReadSynonym(mockStatementsThatRead[i],
      attrRefValue));
  }

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_READ_VARNAME_permutation_noResults") {
  // read r; select r with r.varName = readMe
  SynonymArg withSynonym = SynonymArg("r");
  Entity synonymEntity = READ_ENTITY;
  AttrRef attrRef = VARNAME_ATTRREF;
  string attrRefValue = "readMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  vector<string> mockStatementsThatRead = {};
  mockPkbReader.mockStatmentsThatRead = mockStatementsThatRead;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_PRINT_STMTNUM_permutation") {
  // print p; select p with p.stmmt# = 97
  SynonymArg withSynonym = SynonymArg("p");
  Entity synonymEntity = PRINT_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "97";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  vector<string> mockVarPrintedBy = {"IWASPRINTED"};
  mockPkbReader.mockVariablePrintedBy = mockVarPrintedBy;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData =
  {{SynonymResFactory::buildPrintSynonym(attrRefValue,
  mockVarPrintedBy)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_PRINT_STMTNUM_permutation_noResults") {
  // print p; select p with p.stmmt# = 97
  SynonymArg withSynonym = SynonymArg("p");
  Entity synonymEntity = PRINT_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "97";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  vector<string> mockVarPrintedBy = {""};
  mockPkbReader.mockVariablePrintedBy = mockVarPrintedBy;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_PRINT_VARNAME_permutation") {
  // print p; select p with p.varName = printMe
  SynonymArg withSynonym = SynonymArg("p");
  Entity synonymEntity = PRINT_ENTITY;
  AttrRef attrRef = VARNAME_ATTRREF;
  string attrRefValue = "printMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  vector<string> mockStmtsThatPrint = {"4", "5", "6"};
  mockPkbReader.mockStatementsThatPrint = mockStmtsThatPrint;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData;
  for (int i = 0; i < mockStmtsThatPrint.size(); i++) {
    expectedData.push_back(SynonymResFactory::buildPrintSynonym(mockStmtsThatPrint[i],
      attrRefValue));
  }

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_PRINT_VARNAME_permutation_noResults") {
  // print p; select p with p.varName = printMe
  SynonymArg withSynonym = SynonymArg("p");
  Entity synonymEntity = PRINT_ENTITY;
  AttrRef attrRef = VARNAME_ATTRREF;
  string attrRefValue = "printMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  vector<string> mockStmtsThatPrint = {};
  mockPkbReader.mockStatementsThatPrint = mockStmtsThatPrint;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_CALL_STMTNUM_permutation") {
  // call c; select c with c.stmt# = 96
  SynonymArg withSynonym = SynonymArg("c");
  Entity synonymEntity = CALL_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "96";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  vector<string> mockProcNameCalledByStmtNum = {"iWasCalled"};
  mockPkbReader.mockProcNameCalledByStmtNum = mockProcNameCalledByStmtNum;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData =
  {{SynonymResFactory::buildCallSynonym(attrRefValue,
  mockProcNameCalledByStmtNum)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_CALL_STMTNUM_permutation_noResults") {
  // call c; select c with c.stmt# = 96
  SynonymArg withSynonym = SynonymArg("c");
  Entity synonymEntity = CALL_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "96";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  vector<string> mockProcNameCalledByStmtNum = {""};
  mockPkbReader.mockProcNameCalledByStmtNum = mockProcNameCalledByStmtNum;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_CALL_PROCNAME_permutation") {
  // call c; select c with c.procName = plsCallMe
  SynonymArg withSynonym = SynonymArg("c");
  Entity synonymEntity = CALL_ENTITY;
  AttrRef attrRef = PROCNAME_ATTRREF;
  string attrRefValue = "plsCallMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  vector<string> mockStmtsThatCall = {"7", "8", "9"};
  mockPkbReader.mockStatementsThatCall = mockStmtsThatCall;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData;
  for (int i = 0; i < mockStmtsThatCall.size(); i++) {
    expectedData.push_back(SynonymResFactory::buildCallSynonym(mockStmtsThatCall[i],
      attrRefValue));
  }

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_CALL_PROCNAME_permutation_noResults") {
  // call c; select c with c.procName = plsCallMe
  SynonymArg withSynonym = SynonymArg("c");
  Entity synonymEntity = CALL_ENTITY;
  AttrRef attrRef = PROCNAME_ATTRREF;
  string attrRefValue = "plsCallMe";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  vector<string> mockStmtsThatCall = {};
  mockPkbReader.mockStatementsThatCall = mockStmtsThatCall;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_WHILE_STMTNUM_permutation") {
  // while w; select w with w.stmt# = 95
  SynonymArg withSynonym = SynonymArg("w");
  Entity synonymEntity = WHILE_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "95";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidStatement = true;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData =
  {{SynonymResFactory::buildDefaultSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_WHILE_STMTNUM_permutation_noResults") {
  // while w; select w with w.stmt# = 95
  SynonymArg withSynonym = SynonymArg("w");
  Entity synonymEntity = WHILE_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "95";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidStatement = false;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_IF_STMTNUM_permutation") {
  // if i; select i with i.stmt# = 94
  SynonymArg withSynonym = SynonymArg("i");
  Entity synonymEntity = IF_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "94";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidStatement = true;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData =
  {{SynonymResFactory::buildDefaultSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_IF_STMTNUM_permutation_noResults") {
  // if i; select i with i.stmt# = 94
  SynonymArg withSynonym = SynonymArg("i");
  Entity synonymEntity = IF_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "94";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidStatement = false;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_ASSIGN_STMTNUM_permutation") {
  // assign a; select a with a.stmt# = 93
  SynonymArg withSynonym = SynonymArg("a");
  Entity synonymEntity = ASSIGN_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "93";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidStatement = true;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData =
  {{SynonymResFactory::buildDefaultSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_ASSIGN_STMTNUM_permutation_noResults") {
  // assign a; select a with a.stmt# = 93
  SynonymArg withSynonym = SynonymArg("a");
  Entity synonymEntity = ASSIGN_ENTITY;
  AttrRef attrRef = STMTNUM_ATTRREF;
  string attrRefValue = "93";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidStatement = false;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_VAR_VARNAME_permutation") {
  // variable v; select v with v.varName = "imAVariable"
  SynonymArg withSynonym = SynonymArg("v");
  Entity synonymEntity = VARIABLE_ENTITY;
  AttrRef attrRef = VARNAME_ATTRREF;
  string attrRefValue = "imAVariable";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidVariable = true;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData =
  {{SynonymResFactory::buildVariableSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_VAR_VARNAME_permutation_noResults") {
  // variable v; select v with v.varName = "imAVariable"
  SynonymArg withSynonym = SynonymArg("v");
  Entity synonymEntity = VARIABLE_ENTITY;
  AttrRef attrRef = VARNAME_ATTRREF;
  string attrRefValue = "imAVariable";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidVariable = false;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_CONSTANT_VALUE_permutation") {
  // constant const; select const with const.value = 93
  SynonymArg withSynonym = SynonymArg("const");
  Entity synonymEntity = CONSTANT_ENTITY;
  AttrRef attrRef = VALUE_ATTRREF;
  string attrRefValue = "93";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidConstant = true;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData =
  {{SynonymResFactory::buildConstantSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_CONSTANT_VALUE_permutation_noResults") {
  // constant const; select const with const.value = 93
  SynonymArg withSynonym = SynonymArg("const");
  Entity synonymEntity = CONSTANT_ENTITY;
  AttrRef attrRef = VALUE_ATTRREF;
  string attrRefValue = "93";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidConstant = false;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}

TEST_CASE("test_withClause_evaluate_PROCEDURE_PROCNAME_permutation") {
  // procedure proc; select proc with proc.procName = "theBestProc"
  SynonymArg withSynonym = SynonymArg("proc");
  Entity synonymEntity = PROCEDURE_ENTITY;
  AttrRef attrRef = PROCNAME_ATTRREF;
  string attrRefValue = "theBestProc";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidProcName = true;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  /*vector<string> actualColNames = actualTable.getColNames();
  TableDataType actualTableData = actualTable.getData();
  TableDataType expectedData =
  {{SynonymResFactory::buildProcSynonym(attrRefValue)}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == withSynonym.getValue());
  REQUIRE(actualTableData == expectedData);*/
}

TEST_CASE("test_withClause_evaluate_PROCEDURE_PROCNAME_permutation_noResults") {
  // procedure proc; select proc with proc.procName = "theBestProc"
  SynonymArg withSynonym = SynonymArg("proc");
  Entity synonymEntity = PROCEDURE_ENTITY;
  AttrRef attrRef = PROCNAME_ATTRREF;
  string attrRefValue = "theBestProc";

  unique_ptr<SynonymArg> withSynonymPtr =
      std::make_unique<SynonymArg>(withSynonym.getValue());

  WithClause withClause = WithClause(std::move(withSynonymPtr), synonymEntity,
                                     attrRef, attrRefValue);

  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStore);

  mockPkbReader.mockIsValidProcName = false;

  // TODO(houten): remove context when merge kh pr
  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      withClause.evaluate(mockContext, mockPkbReader);

  // TODO(houten): integrate with synonymRes
  REQUIRE(actualTable.isTableEmpty());
}
